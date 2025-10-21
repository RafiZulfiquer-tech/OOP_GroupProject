#include <SFML/Graphics.hpp>
#include "Environment.h"
#include "Player.h"
#include "Warrior.h"
#include "Wizard.h"
#include "Rogue.h"
#include "Enemy.h"
#include "Goblin.h"
#include "Controller.h"
#include "Menu.h"
#include "Attack.h"
#include "Leaderboard.h"
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "WaveManager.h"
#include "HUD.h"

int main() {
    // Seed random number generator for randomness in game
    srand(static_cast<unsigned>(time(0)));
    
    // Create the main window with resolution 1280x720
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Goblin Slayer");
    window.setFramerateLimit(60);  // Cap FPS at 60
    
    // Initialize core game components
    Environment environment(1280, 720);
    WaveManager waveManager(&environment);
    Controller controller;
    Menu menu;

    // Load font for text rendering (warning if failed)
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Warning: Could not load arial.ttf. Text will not display." << std::endl;
    }

    Player* player = nullptr;  // Pointer to current player character
    std::vector<std::unique_ptr<Attack>> attacks;  // Active player attacks
    MenuState gameState = MenuState::MAIN_MENU;  // Initial game state
    sf::Clock clock;  // Clock for delta time
    HUD hud(font);    // Heads-up display initialized with font
    menu.setFont(font);
    Leaderboard leaderboard("leaderboard.txt");  // Load leaderboard

    // Variables to store stats for end-of-game screen and saving scores
    int finalWave = 0;
    int finalKills = 0;
    int finalLevel = 0;
    std::string finalClassName = "";

    std::cout << "Game started! Use mouse to navigate menus." << std::endl;

    // Main game loop - runs while window is open
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();  // Time elapsed since last frame

        sf::Event event;
        // Process all events
        while (window.pollEvent(event)) {
            // Handle window close event
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle input/events depending on current game state
            if (gameState == MenuState::MAIN_MENU || gameState == MenuState::CLASS_SELECT) {
                // Handle mouse clicks for menu navigation
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    int selection = menu.handleClick(mousePos);

                    if (gameState == MenuState::MAIN_MENU) {
                        // Main menu options: Start Game, Leaderboard, Quit
                        if (selection == 0) { // Start Game selected
                            menu.setState(MenuState::CLASS_SELECT);
                            gameState = MenuState::CLASS_SELECT;
                        } else if (selection == 1) { // Leaderboard selected
                            menu.setState(MenuState::LEADERBOARD);
                            gameState = MenuState::LEADERBOARD;
                        } else if (selection == 2) { // Quit selected
                            window.close();
                        }
                    } else if (gameState == MenuState::CLASS_SELECT) {
                        // Player class selection screen
                        if (selection >= 0) {
                            // Clean up previous game objects if restarting
                            if (player) {
                                delete player;
                                player = nullptr;
                            }
                            // Delete all entities in environment (enemies, etc.)
                            for (size_t i = 0; i < environment.getEntityCount(); ++i) {
                                delete environment.getEntity(i);
                            }
                            environment.clearEntities();
                            attacks.clear();

                            // Reset wave manager for new game
                            waveManager = WaveManager(&environment);

                            // Create player character based on class selection
                            if (selection == 0) player = new Warrior(640, 360);
                            else if (selection == 1) player = new Wizard(640, 360);
                            else if (selection == 2) player = new Rogue(640, 360);

                            gameState = MenuState::PLAYING;  // Transition to gameplay
                            std::cout << "Game started with " << player->getClassName() << std::endl;
                        }
                    }
                }
            } else if (gameState == MenuState::PLAYING) {
                // Gameplay input handling
                controller.handleEvent(event);

                // Press ESC to pause game
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    std::cout << "Game paused" << std::endl;
                    gameState = MenuState::PAUSED;
                }
            } else if (gameState == MenuState::PAUSED) {
                // Pause menu controls
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    // Resume game on ESC
                    std::cout << "Game resumed" << std::endl;
                    gameState = MenuState::PLAYING;
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    // Restart game on R
                    std::cout << "Restarting game..." << std::endl;
                    menu.setState(MenuState::CLASS_SELECT);
                    gameState = MenuState::CLASS_SELECT;
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
                    // Quit to main menu on Q
                    std::cout << "Returning to main menu..." << std::endl;

                    // Cleanup player and environment entities
                    if (player) {
                        delete player;
                        player = nullptr;
                    }
                    for (size_t i = 0; i < environment.getEntityCount(); ++i) {
                        delete environment.getEntity(i);
                    }
                    environment.clearEntities();
                    attacks.clear();

                    menu.setState(MenuState::MAIN_MENU);
                    gameState = MenuState::MAIN_MENU;
                }
            } else if (gameState == MenuState::GAME_OVER) {
                // Game over screen input handling
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    // Restart game on R
                    std::cout << "Restarting game..." << std::endl;

                    // Save score if it qualifies for leaderboard
                    if (leaderboard.isTopScore(finalWave)) {
                        std::cout << "Enter your name (no spaces): ";
                        std::string playerName;
                        std::cin >> playerName;
                        std::cout << "Saving score..." << std::endl;
                        leaderboard.addScore(playerName, finalClassName,
                                           finalWave, finalKills, finalLevel);
                        std::cout << "Score saved!" << std::endl;
                    }

                    // Cleanup previous game data
                    std::cout << "Cleaning up player..." << std::endl;
                    if (player) {
                        delete player;
                        player = nullptr;
                    }

                    std::cout << "Cleaning up entities..." << std::endl;
                    environment.clearEntities();

                    std::cout << "Cleaning up attacks..." << std::endl;
                    attacks.clear();

                    std::cout << "Cleanup complete! Starting new game..." << std::endl;
                    menu.setState(MenuState::CLASS_SELECT);
                    gameState = MenuState::CLASS_SELECT;
                }
                else if (event.type == sf::Event::KeyPressed &&
                         (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Q)) {
                    // Return to main menu on ESC or Q
                    std::cout << "Returning to main menu..." << std::endl;

                    // Save score if top score
                    if (leaderboard.isTopScore(finalWave)) {
                        std::cout << "Enter your name (no spaces): ";
                        std::string playerName;
                        std::cin >> playerName;
                        std::cout << "Saving score..." << std::endl;
                        leaderboard.addScore(playerName, finalClassName,
                                           finalWave, finalKills, finalLevel);
                        std::cout << "Score saved!" << std::endl;
                    }

                    // Cleanup previous game data
                    std::cout << "Cleaning up player..." << std::endl;
                    if (player) {
                        delete player;
                        player = nullptr;
                    }

                    std::cout << "Cleaning up entities..." << std::endl;
                    environment.clearEntities();

                    std::cout << "Cleaning up attacks..." << std::endl;
                    attacks.clear();

                    std::cout << "Cleanup complete! Returning to menu..." << std::endl;
                    menu.setState(MenuState::MAIN_MENU);
                    gameState = MenuState::MAIN_MENU;
                    std::cout << "State changed to MAIN_MENU" << std::endl;
                }
            } else if (gameState == MenuState::LEADERBOARD) {
                // Exit leaderboard screen on ESC key
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    menu.setState(MenuState::MAIN_MENU);
                    gameState = MenuState::MAIN_MENU;
                }
            }
        }

        // Update mouse hover for menu buttons
        if (gameState == MenuState::MAIN_MENU || gameState == MenuState::CLASS_SELECT) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            menu.handleMouseMove(mousePos);
        }

        // Update game logic when playing (not paused or in menu)
        if (gameState == MenuState::PLAYING && player) {
            // Update input controller for movement and attacks
            controller.update(window);

            // Move player character based on input
            sf::Vector2f moveVec = controller.getMoveVector();
            player->move(moveVec, deltaTime);

            // Handle player attack input
            if (controller.isAttackPressed()) {
                if (player->canAttack()) {
                    float angleToMouse = controller.getMouseAngle(player->getPosition());
                    auto attack = player->createAttack(angleToMouse);
                    if (attack) {
                        attacks.push_back(std::move(attack));
                        player->resetCooldown();
                    }
                }
            }

            // Update player state (cooldowns, animations, etc.)
            player->update(deltaTime);

            // Update wave manager (spawn enemies, handle wave logic)
            waveManager.update(deltaTime);

            // Update HUD with current game stats
            hud.update(waveManager.getCurrentWave(),
                       player->getHealth(),
                       player->getMaxHealth(),
                       player->getKills(),
                       player->getXP(),
                       player->getXPNeeded(),
                       player->getLevel(),
                       player->getClassName());

            // Update enemies: move toward player and attack
            for (size_t i = 0; i < environment.getEntityCount(); ++i) {
                Entity* entity = environment.getEntity(i);
                Enemy* enemy = dynamic_cast<Enemy*>(entity);
                if (enemy && enemy->isAlive()) {
                    enemy->moveToward(player->getPosition(), deltaTime);
                    enemy->update(deltaTime);

                    // Check if enemy is close enough to attack player
                    float dist = std::sqrt(
                        std::pow(enemy->getPosition().x - player->getPosition().x, 2) +
                        std::pow(enemy->getPosition().y - player->getPosition().y, 2)
                    );
                    if (dist < 30.f && enemy->canAttack()) {
                        player->takeDamage(enemy->getDamage());
                        enemy->resetCooldown();

                        // Check if player died from attack
                        if (!player->isAlive()) {
                            // Store final stats for game over screen and leaderboard
                            finalWave = waveManager.getCurrentWave();
                            finalKills = player->getKills();
                            finalLevel = player->getLevel();
                            finalClassName = player->getClassName();

                            std::cout << "Game Over! Wave: " << finalWave
                                      << " Kills: " << finalKills << std::endl;

                            // Switch to game over state, defer cleanup to input handler
                            gameState = MenuState::GAME_OVER;
                        }
                    }
                }
            }

            // Update all active attacks and check collision with enemies
            for (auto& attack : attacks) {
                attack->update(deltaTime);

                for (size_t i = 0; i < environment.getEntityCount(); ++i) {
                    Enemy* enemy = dynamic_cast<Enemy*>(environment.getEntity(i));
                    if (enemy && enemy->isAlive() && attack->isActive()) {
                        if (!attack->hasHit(enemy) && attack->checkCollision(enemy->getPosition(), enemy->getRadius())) {
                            enemy->takeDamage(attack->getDamage());
                            attack->markHit(enemy);
                            attack->deactivate();

                            // Reward player on enemy kill
                            if (!enemy->isAlive()) {
                                player->addKill();
                                player->addXP(enemy->getXPReward());
                            }
                        }
                    }
                }
            }

            // Remove all inactive attacks from the vector
            attacks.erase(
                std::remove_if(attacks.begin(), attacks.end(),
                               [](const std::unique_ptr<Attack>& a) { return !a->isActive(); }),
                attacks.end()
            );

            // Remove dead enemies/entities from environment if player is still alive
            if (gameState == MenuState::PLAYING && player && player->isAlive()) {
                environment.removeDeadEntities();
            }
        }

        // Begin rendering frame
        window.clear(sf::Color(30, 30, 40));  // Dark background

        // Draw appropriate screen based on game state
        if (gameState == MenuState::MAIN_MENU || gameState == MenuState::CLASS_SELECT) {
            menu.draw(window);
        } else if (gameState == MenuState::LEADERBOARD) {
            leaderboard.draw(window, font);
        } else if (gameState == MenuState::PLAYING && player) {
            // Draw player
            player->draw(window);

            // Draw all alive enemies
            for (size_t i = 0; i < environment.getEntityCount(); ++i) {
                Enemy* enemy = dynamic_cast<Enemy*>(environment.getEntity(i));
                if (enemy && enemy->isAlive()) {
                    enemy->draw(window);
                }
            }

            // Draw all active attacks
            for (auto& attack : attacks) {
                attack->draw(window);
            }

            // Draw HUD on top
            hud.draw(window);

        } else if (gameState == MenuState::PAUSED) {
            // Draw paused game screen with dark overlay and instructions

            if (player) player->draw(window);

            for (size_t i = 0; i < environment.getEntityCount(); ++i) {
                Enemy* enemy = dynamic_cast<Enemy*>(environment.getEntity(i));
                if (enemy && enemy->isAlive()) enemy->draw(window);
            }

            for (auto& attack : attacks) attack->draw(window);

            hud.draw(window);

            // Overlay rectangle for pause message
            sf::RectangleShape overlay(sf::Vector2f(1280, 720));
            overlay.setFillColor(sf::Color(0, 0, 0, 150));
            window.draw(overlay);

            sf::Text pauseText("Paused\nESC to Resume\nR to Restart\nQ to Quit", font, 24);
            pauseText.setFillColor(sf::Color::White);
            pauseText.setPosition(500, 300);
            window.draw(pauseText);

        } else if (gameState == MenuState::GAME_OVER) {
            // Game over screen showing final stats and options to restart or quit

            sf::Text gameOverText("GAME OVER", font, 48);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(500, 200);
            window.draw(gameOverText);

            std::string stats = "Wave: " + std::to_string(finalWave) +
                                "\nKills: " + std::to_string(finalKills) +
                                "\nLevel: " + std::to_string(finalLevel) +
                                "\nClass: " + finalClassName;

            sf::Text statsText(stats, font, 24);
            statsText.setFillColor(sf::Color::White);
            statsText.setPosition(500, 280);
            window.draw(statsText);

            sf::Text instructions("Press R to Restart\nPress Q or ESC to Quit to Menu", font, 20);
            instructions.setFillColor(sf::Color::White);
            instructions.setPosition(450, 400);
            window.draw(instructions);
        }

        window.display();  // Show rendered frame
    }

    // Cleanup player if still allocated before exit
    if (player) {
        delete player;
        player = nullptr;
    }

    // Cleanup environment entities
    environment.clearEntities();

    return 0;
}