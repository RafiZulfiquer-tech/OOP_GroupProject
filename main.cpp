#include <SFML/Graphics.hpp>
#include "environment.h"
#include "Player.h"
#include "Warrior.h"
#include "Wizard.h"
#include "Rogue.h"
#include "Enemy.h"
#include "Goblin.h"
#include "Controller.h"
#include "Menu.h"
#include "Attack.h"
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand(static_cast<unsigned>(time(0)));
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Goblin Slayer");
    window.setFramerateLimit(60);

    Environment environment(1280, 720);
    Controller controller;
    Menu menu;
    
    if (!menu.loadFont("arial.ttf")) {
        std::cout << "Warning: Could not load arial.ttf. Text will not display." << std::endl;
    }

    Player* player = nullptr;
    std::vector<Enemy*> enemies;
    std::vector<std::unique_ptr<Attack>> attacks;
    MenuState gameState = MenuState::MAIN_MENU;
    sf::Clock clock;
    float spawnTimer = 0.f;
    float spawnInterval = 3.f;

    std::cout << "Game started! Use mouse to navigate menus." << std::endl;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (gameState == MenuState::MAIN_MENU || gameState == MenuState::CLASS_SELECT) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    int selection = menu.handleClick(mousePos);
                    
                    if (gameState == MenuState::MAIN_MENU) {
                        if (selection == 0) { // Start Game
                            menu.setState(MenuState::CLASS_SELECT);
                            gameState = MenuState::CLASS_SELECT;
                        } else if (selection == 3) { // Quit
                            window.close();
                        }
                    } else if (gameState == MenuState::CLASS_SELECT) {
                        if (selection >= 0) {
                            // Create player based on selection
                            if (selection == 0) player = new Warrior(640, 360);
                            else if (selection == 1) player = new Wizard(640, 360);
                            else if (selection == 2) player = new Rogue(640, 360);
                            
                            gameState = MenuState::PLAYING;
                            std::cout << "Game started with " << player->getClassName() << std::endl;
                        }
                    }
                }
            } else if (gameState == MenuState::PLAYING) {
                controller.handleEvent(event);
                
                // ESC to pause
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    gameState = MenuState::PAUSED;
                }
            } else if (gameState == MenuState::GAME_OVER) {
                // ESC to return to main menu
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    // Clean up current game
                    if (player) {
                        delete player;
                        player = nullptr;
                    }
                    for (auto enemy : enemies) delete enemy;
                    enemies.clear();
                    attacks.clear();
                    
                    // Return to main menu
                    menu.setState(MenuState::MAIN_MENU);
                    gameState = MenuState::MAIN_MENU;
                }
            }
        }

        // Update mouse position for menu hover effects
        if (gameState == MenuState::MAIN_MENU || gameState == MenuState::CLASS_SELECT) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            menu.handleMouseMove(mousePos);
        }

        // Game logic
        if (gameState == MenuState::PLAYING && player) {
            controller.update(window);
            
            // Player movement
            sf::Vector2f moveVec = controller.getMoveVector();
            player->move(moveVec, deltaTime);
            
            // Player attack
            if (controller.isAttackPressed()) {
                std::cout << "Click detected! Can attack: " << player->canAttack() 
                          << " Cooldown: " << player->getCooldown() << std::endl;
                if (player->canAttack()) {
                    float angleToMouse = controller.getMouseAngle(player->getPosition());
                    auto attack = player->createAttack(angleToMouse);
                    if (attack) {
                        attacks.push_back(std::move(attack));
                        player->resetCooldown();
                        std::cout << "Attack created! Angle: " << angleToMouse 
                                  << " Total attacks: " << attacks.size() << std::endl;
                    } else {
                        std::cout << "Attack creation failed (probably out of mana)" << std::endl;
                    }
                }
            }
            
            // Update player
            player->update(deltaTime);
            
            // Spawn enemies
            spawnTimer += deltaTime;
            if (spawnTimer >= spawnInterval) {
                float x = rand() % 1280;
                float y = rand() % 720;
                enemies.push_back(new Goblin(x, y));
                spawnTimer = 0.f;
            }
            
            // Update enemies
            for (auto enemy : enemies) {
                if (enemy->isAlive()) {
                    enemy->moveToward(player->getPosition(), deltaTime);
                    enemy->update(deltaTime);
                    
                    // Check enemy attack on player
                    float dist = std::sqrt(
                        std::pow(enemy->getPosition().x - player->getPosition().x, 2) +
                        std::pow(enemy->getPosition().y - player->getPosition().y, 2)
                    );
                    if (dist < 30.f && enemy->canAttack()) {
                        player->takeDamage(enemy->getDamage());
                        enemy->resetCooldown();
                        if (!player->isAlive()) {
                            gameState = MenuState::GAME_OVER;
                            std::cout << "Game Over! Kills: " << player->getKills() << std::endl;
                        }
                    }
                }
            }
            
            // Update attacks
            for (auto& attack : attacks) {
                attack->update(deltaTime);
                
                // Check attack collision with enemies
                for (auto enemy : enemies) {
                    if (enemy->isAlive() && attack->isActive()) {
                        // Check if this enemy was already hit by this attack
                        if (!attack->hasHit(enemy) && attack->checkCollision(enemy->getPosition(), enemy->getRadius())) {
                            enemy->takeDamage(attack->getDamage());
                            attack->markHit(enemy); // Mark as hit
                            attack->deactivate(); // This only deactivates projectiles, not slashes
                            if (!enemy->isAlive()) {
                                player->addKill();
                                player->addXP(enemy->getXPReward());
                            }
                        }
                    }
                }
            }
            
            // Remove inactive attacks
            attacks.erase(
                std::remove_if(attacks.begin(), attacks.end(),
                    [](const std::unique_ptr<Attack>& a) { return !a->isActive(); }),
                attacks.end()
            );
            
            // Remove dead enemies
            enemies.erase(
                std::remove_if(enemies.begin(), enemies.end(),
                    [](Enemy* e) {
                        if (!e->isAlive()) {
                            delete e;
                            return true;
                        }
                        return false;
                    }),
                enemies.end()
            );
        }

        // Rendering
        window.clear(sf::Color(30, 30, 40));
        
        if (gameState == MenuState::MAIN_MENU || gameState == MenuState::CLASS_SELECT) {
            menu.draw(window);
        } else if (gameState == MenuState::PLAYING && player) {
            // Draw player
            player->draw(window);
            
            // Draw enemies
            for (auto enemy : enemies) {
                enemy->draw(window);
            }
            
            // Draw attacks
            for (auto& attack : attacks) {
                attack->draw(window);
            }
            
            // Draw HUD (simple text)
            if (menu.loadFont("arial.ttf")) {
                // You could add HUD elements here
            }
        } else if (gameState == MenuState::GAME_OVER) {
            // Simple game over screen
            sf::Text gameOverText;
            sf::Font font;
            if (font.loadFromFile("arial.ttf")) {
                gameOverText.setFont(font);
                gameOverText.setString("GAME OVER\n\nKills: " + std::to_string(player ? player->getKills() : 0) + 
                                      "\n\nPress ESC to return to menu");
                gameOverText.setCharacterSize(48);
                gameOverText.setFillColor(sf::Color::Red);
                sf::FloatRect bounds = gameOverText.getLocalBounds();
                gameOverText.setOrigin(bounds.width / 2, bounds.height / 2);
                gameOverText.setPosition(640, 360);
                window.draw(gameOverText);
            }
        }
        
        window.display();
    }

    // Cleanup
    if (player) delete player;
    for (auto enemy : enemies) delete enemy;
    
    return 0;
}