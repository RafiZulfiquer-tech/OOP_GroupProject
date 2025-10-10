#include <SFML/Graphics.hpp>
#include "Environment.h"
#include "Player.h"
#include "Enemy.h"
#include "Controller.h"
#include "Menu.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand(static_cast<unsigned>(time(0)));
    
    // Window setup
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Goblin Slayer");
    window.setFramerateLimit(60);
    
    // Initialize systems
    Environment environment(1280, 720);
    Controller controller;
    Menu menu;
    
    // Load font
    if (!menu.loadFont("arial.ttf")) {
        std::cout << "Warning: Could not load arial.ttf. Text will not display." << std::endl;
    }
    
    // Game state
    Player* player = nullptr;
    std::vector<Enemy*> enemies;
    MenuState gameState = MenuState::MAIN_MENU;
    
    sf::Clock clock;
    
    std::cout << "Game started! Use mouse to navigate menus." << std::endl;
    
    // Main game loop
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Mouse move for menu hover effects
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                menu.handleMouseMove(mousePos);
            }
            
            // Mouse click for menu selections
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                
                if (gameState == MenuState::MAIN_MENU) {
                    int choice = menu.handleClick(mousePos);
                    if (choice == 0) {  // Start Game
                        std::cout << "Starting game - Select your class!" << std::endl;
                        menu.setState(MenuState::CLASS_SELECT);
                        gameState = MenuState::CLASS_SELECT;
                    } else if (choice == 1) {  // Settings
                        std::cout << "Settings not implemented yet" << std::endl;
                    } else if (choice == 2) {  // Leaderboard
                        std::cout << "Leaderboard not implemented yet" << std::endl;
                    } else if (choice == 3) {  // Quit
                        std::cout << "Quitting game..." << std::endl;
                        window.close();
                    }
                } else if (gameState == MenuState::CLASS_SELECT) {
                    int classChoice = menu.handleClick(mousePos);
                    if (classChoice >= 0) {
                        std::string className;
                        if (classChoice == 0) {
                            className = "Warrior";
                        } else if (classChoice == 1) {
                            className = "Wizard";
                        } else {
                            className = "Rogue";
                        }
                        
                        std::cout << "You selected: " << className << std::endl;
                        
                        // Cleanup old player if exists
                        if (player) {
                            environment.removeEntity(player);
                            delete player;
                            player = nullptr;
                        }
                        
                        // Create new player at center
                        player = new Player(640.f, 360.f);
                        environment.spawnEntity(player);
                        
                        // Clear old enemies
                        for (auto* enemy : enemies) {
                            environment.removeEntity(enemy);
                            delete enemy;
                        }
                        enemies.clear();
                        
                        std::cout << "Spawning enemies..." << std::endl;
                        
                        // Spawn 5 weak goblins
                        for (int i = 0; i < 5; i++) {
                            float x, y;
                            int edge = rand() % 4;
                            switch(edge) {
                                case 0: x = rand() % 1280; y = 0; break;       // Top
                                case 1: x = 1280; y = rand() % 720; break;     // Right
                                case 2: x = rand() % 1280; y = 720; break;     // Bottom
                                case 3: x = 0; y = rand() % 720; break;        // Left
                            }
                            
                            // hp=50, speed=120, damage=10
                            Enemy* goblin = new Enemy(x, y, 50, 120.f, 10);
                            enemies.push_back(goblin);
                            environment.spawnEntity(goblin);
                        }
                        
                        // Spawn 2 stronger brutes
                        for (int i = 0; i < 2; i++) {
                            float x, y;
                            int edge = rand() % 4;
                            switch(edge) {
                                case 0: x = rand() % 1280; y = 0; break;
                                case 1: x = 1280; y = rand() % 720; break;
                                case 2: x = rand() % 1280; y = 720; break;
                                case 3: x = 0; y = rand() % 720; break;
                            }
                            
                            // hp=100, speed=80, damage=20
                            Enemy* brute = new Enemy(x, y, 100, 80.f, 20);
                            enemies.push_back(brute);
                            environment.spawnEntity(brute);
                        }
                        
                        // Spawn 1 boss
                        float x, y;
                        int edge = rand() % 4;
                        switch(edge) {
                            case 0: x = rand() % 1280; y = 0; break;
                            case 1: x = 1280; y = rand() % 720; break;
                            case 2: x = rand() % 1280; y = 720; break;
                            case 3: x = 0; y = rand() % 720; break;
                        }
                        
                        // hp=200, speed=100, damage=30
                        Enemy* boss = new Enemy(x, y, 200, 100.f, 30);
                        enemies.push_back(boss);
                        environment.spawnEntity(boss);
                        
                        std::cout << "Game starting! Total enemies: " << enemies.size() << std::endl;
                        std::cout << "Controls: WASD - Move, Left Click - Attack, ESC - Menu" << std::endl;
                        
                        // Start playing
                        gameState = MenuState::PLAYING;
                        menu.setState(MenuState::PLAYING);
                    }
                }
            }
            
            // Game input events (only when playing)
            if (gameState == MenuState::PLAYING) {
                controller.handleEvent(event);
                
                // ESC to pause/return to menu
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    std::cout << "Returning to main menu..." << std::endl;
                    gameState = MenuState::MAIN_MENU;
                    menu.setState(MenuState::MAIN_MENU);
                }
            }
            
            // ESC on game over to return to menu
            if (gameState == MenuState::GAME_OVER) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    std::cout << "Returning to main menu from game over..." << std::endl;
                    gameState = MenuState::MAIN_MENU;
                    menu.setState(MenuState::MAIN_MENU);
                }
            }
        }
        
        // Update (only when playing)
        if (gameState == MenuState::PLAYING && player) {
            controller.update(window);
            
            // Player movement using Controller
            sf::Vector2f moveVec = controller.getMoveVector();
            player->move(moveVec, deltaTime);
            
            // Player attack
            if (controller.isAttackPressed() && player->canAttack()) {
                player->attack();
                std::cout << "Player attacked!" << std::endl;
                // TODO: Check if attack hit any enemies
            }
            
            // Update player
            player->update(deltaTime);
            
            // Update all enemies
            for (auto* enemy : enemies) {
                if (enemy->isAlive()) {
                    // Enemy chases player
                    enemy->moveToward(player->getPosition(), deltaTime);
                    
                    // Update enemy
                    enemy->update(deltaTime);
                    
                    // Check collision between player and enemy
                    if (environment.checkCollision(player, enemy)) {
                        // Enemy attacks player if cooldown ready
                        if (enemy->canAttack()) {
                            player->takeDamage(enemy->getDamage());
                            enemy->resetCooldown();
                            std::cout << "Enemy hit player! HP: " << player->getHealth() << std::endl;
                        }
                    }
                }
            }
            
            // Check if player is dead
            if (!player->isAlive()) {
                std::cout << "Player died! Game Over!" << std::endl;
                std::cout << "Final Stats - Level: " << player->getLevel() 
                          << " | Kills: " << player->getKills() << std::endl;
                gameState = MenuState::GAME_OVER;
            }
        }
        
        // Render
        window.clear(sf::Color(30, 30, 40));
        
        if (gameState == MenuState::PLAYING) {
            // Draw arena background
            sf::RectangleShape arena(sf::Vector2f(1280, 720));
            arena.setFillColor(sf::Color(40, 40, 40));
            window.draw(arena);
            
            // Draw border
            sf::RectangleShape border(sf::Vector2f(1280, 720));
            border.setFillColor(sf::Color::Transparent);
            border.setOutlineColor(sf::Color(100, 100, 100));
            border.setOutlineThickness(5.f);
            window.draw(border);
            
            // Draw entities
            if (player) {
                player->draw(window);
            }
            
            for (auto* enemy : enemies) {
                if (enemy->isAlive()) {
                    enemy->draw(window);
                }
            }
            
            // Draw simple HUD
            sf::Font font;
            if (font.loadFromFile("arial.ttf") && player) {
                // Health display
                sf::Text healthText;
                healthText.setFont(font);
                healthText.setString("HP: " + std::to_string(player->getHealth()) + 
                                    "/" + std::to_string(player->getMaxHealth()));
                healthText.setCharacterSize(24);
                healthText.setFillColor(sf::Color::White);
                healthText.setPosition(10, 10);
                window.draw(healthText);
                
                // Level display
                sf::Text levelText;
                levelText.setFont(font);
                levelText.setString("Level: " + std::to_string(player->getLevel()));
                levelText.setCharacterSize(24);
                levelText.setFillColor(sf::Color::Yellow);
                levelText.setPosition(10, 40);
                window.draw(levelText);
                
                // XP display
                sf::Text xpText;
                xpText.setFont(font);
                xpText.setString("XP: " + std::to_string(player->getXP()));
                xpText.setCharacterSize(24);
                xpText.setFillColor(sf::Color::Magenta);
                xpText.setPosition(10, 70);
                window.draw(xpText);
                
                // Kills display
                sf::Text killsText;
                killsText.setFont(font);
                killsText.setString("Kills: " + std::to_string(player->getKills()));
                killsText.setCharacterSize(24);
                killsText.setFillColor(sf::Color::Green);
                killsText.setPosition(10, 100);
                window.draw(killsText);
                
                // Class display
                sf::Text classText;
                classText.setFont(font);
                classText.setString("Class: " + player->getClassName());
                classText.setCharacterSize(24);
                classText.setFillColor(sf::Color::Cyan);
                classText.setPosition(10, 130);
                window.draw(classText);
                
                // Enemy count
                int aliveEnemies = 0;
                for (auto* enemy : enemies) {
                    if (enemy->isAlive()) aliveEnemies++;
                }
                sf::Text enemyText;
                enemyText.setFont(font);
                enemyText.setString("Enemies: " + std::to_string(aliveEnemies));
                enemyText.setCharacterSize(24);
                enemyText.setFillColor(sf::Color::Red);
                enemyText.setPosition(10, 160);
                window.draw(enemyText);
                
                // Attack cooldown indicator
                if (!player->canAttack()) {
                    sf::Text cooldownText;
                    cooldownText.setFont(font);
                    cooldownText.setString("Reloading...");
                    cooldownText.setCharacterSize(20);
                    cooldownText.setFillColor(sf::Color::Red);
                    cooldownText.setPosition(10, 190);
                    window.draw(cooldownText);
                }
                
                // Controls hint
                sf::Text controlsText;
                controlsText.setFont(font);
                controlsText.setString("WASD - Move | Left Click - Attack | ESC - Menu");
                controlsText.setCharacterSize(18);
                controlsText.setFillColor(sf::Color(150, 150, 150));
                controlsText.setPosition(10, 680);
                window.draw(controlsText);
            }
            
        } else if (gameState == MenuState::GAME_OVER) {
            // Game over screen
            sf::Font font;
            if (font.loadFromFile("arial.ttf")) {
                sf::Text gameOverText;
                gameOverText.setFont(font);
                gameOverText.setString("GAME OVER");
                gameOverText.setCharacterSize(80);
                gameOverText.setFillColor(sf::Color::Red);
                gameOverText.setStyle(sf::Text::Bold);
                sf::FloatRect bounds = gameOverText.getLocalBounds();
                gameOverText.setOrigin(bounds.width / 2, bounds.height / 2);
                gameOverText.setPosition(640, 300);
                window.draw(gameOverText);
                
                // Show stats
                if (player) {
                    sf::Text statsText;
                    statsText.setFont(font);
                    statsText.setString("Level: " + std::to_string(player->getLevel()) + "\n" +
                                       "Kills: " + std::to_string(player->getKills()) + "\n\n" +
                                       "Press ESC for Menu");
                    statsText.setCharacterSize(30);
                    statsText.setFillColor(sf::Color::White);
                    sf::FloatRect statsBounds = statsText.getLocalBounds();
                    statsText.setOrigin(statsBounds.width / 2, statsBounds.height / 2);
                    statsText.setPosition(640, 450);
                    window.draw(statsText);
                }
            }
            
        } else {
            // Draw menu
            menu.draw(window);
        }
        
        window.display();
    }
    
    // Cleanup
    std::cout << "Cleaning up resources..." << std::endl;
    if (player) {
        delete player;
    }
    for (auto* enemy : enemies) {
        delete enemy;
    }
    
    std::cout << "Game closed successfully!" << std::endl;
    
    return 0;
}