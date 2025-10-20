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
#include "Leaderboard.h"
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "WaveManager.h"
#include "HUD.h"

int main() {
    srand(static_cast<unsigned>(time(0)));
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Goblin Slayer");
    window.setFramerateLimit(60);

    Environment environment(1280, 720);
    WaveManager waveManager(&environment);
    Controller controller;
    Menu menu;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Warning: Could not load arial.ttf. Text will not display." << std::endl;
    }

    Player* player = nullptr;
    std::vector<std::unique_ptr<Attack>> attacks;
    MenuState gameState = MenuState::MAIN_MENU;
    sf::Clock clock;
    HUD hud(font);
    menu.setFont(font);
    Leaderboard leaderboard("leaderboard.txt");

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
                        } else if (selection == 1) { // Leaderboard
                            menu.setState(MenuState::LEADERBOARD);
                            gameState = MenuState::LEADERBOARD;
                        } else if (selection == 2) { // Quit
                            window.close();
                        }
                    } else if (gameState == MenuState::CLASS_SELECT) {
                        if (selection >= 0) {
                            // Clean up old game if restarting
                            if (player) {
                                delete player;
                                player = nullptr;
                            }
                            for (size_t i = 0; i < environment.getEntityCount(); ++i) {
                                delete environment.getEntity(i);
                            }
                            environment.clearEntities();
                            attacks.clear();
                            
                            // Reset wave manager
                            waveManager = WaveManager(&environment);

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
                    std::cout << "Game paused" << std::endl;
                    gameState = MenuState::PAUSED;
                }
            } else if (gameState == MenuState::PAUSED) {
                // ESC to unpause
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    std::cout << "Game resumed" << std::endl;
                    gameState = MenuState::PLAYING;
                }
                // R to restart
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    std::cout << "Restarting game..." << std::endl;
                    menu.setState(MenuState::CLASS_SELECT);
                    gameState = MenuState::CLASS_SELECT;
                }
                // Q to quit to main menu
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
                    std::cout << "Returning to main menu..." << std::endl;
                    
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
                // R to restart
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    std::cout << "Restarting game..." << std::endl;
                    
                    // Save score to leaderboard if it's a top score
                    if (player && leaderboard.isTopScore(waveManager.getCurrentWave())) {
                        std::cout << "Enter your name (no spaces): ";
                        std::string playerName;
                        std::cin >> playerName;
                        leaderboard.addScore(playerName, player->getClassName(), 
                                           waveManager.getCurrentWave(), 
                                           player->getKills(), 
                                           player->getLevel());
                    }
                    
                    // Clean up AFTER saving score
                    if (player) {
                        delete player;
                        player = nullptr;
                    }
                    for (size_t i = 0; i < environment.getEntityCount(); ++i) {
                        delete environment.getEntity(i);
                    }
                    environment.clearEntities();
                    attacks.clear();
                    
                    menu.setState(MenuState::CLASS_SELECT);
                    gameState = MenuState::CLASS_SELECT;
                    break;  // Break out of event loop
                }
                // ESC or Q to return to main menu
                else if (event.type == sf::Event::KeyPressed && 
                    (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Q)) {
                    std::cout << "Returning to main menu..." << std::endl;
                    
                    // Save score to leaderboard if it's a top score
                    if (player && leaderboard.isTopScore(waveManager.getCurrentWave())) {
                        std::cout << "Enter your name (no spaces): ";
                        std::string playerName;
                        std::cin >> playerName;
                        leaderboard.addScore(playerName, player->getClassName(), 
                                           waveManager.getCurrentWave(), 
                                           player->getKills(), 
                                           player->getLevel());
                    }
                    
                    // Clean up AFTER saving score
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
                    break;  // Break out of event loop
                }
            } else if (gameState == MenuState::LEADERBOARD) {
                // ESC to return to main menu from leaderboard
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
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

        // Game logic (only when playing, not paused)
        if (gameState == MenuState::PLAYING && player) {
            controller.update(window);

            // Player movement
            sf::Vector2f moveVec = controller.getMoveVector();
            player->move(moveVec, deltaTime);

            // Player attack
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

            // Update player
            player->update(deltaTime);

            // Update waveManager
            waveManager.update(deltaTime);

            // Update HUD
            hud.update(waveManager.getCurrentWave(), 
                      player->getHealth(), 
                      player->getMaxHealth(),
                      player->getKills(),
                      player->getXP(),
                      player->getXPNeeded(),
                      player->getLevel(),
                      player->getClassName());

            // Update enemies
            for (size_t i = 0; i < environment.getEntityCount(); ++i) {
                Entity* entity = environment.getEntity(i);
                Enemy* enemy = dynamic_cast<Enemy*>(entity);
                if (enemy && enemy->isAlive()) {
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
                            std::cout << "Game Over! Wave: " << waveManager.getCurrentWave() 
                                     << " Kills: " << player->getKills() << std::endl;
                        }
                    }
                }
            }

            // Update attacks
            for (auto& attack : attacks) {
                attack->update(deltaTime);

                // Check attack collision with enemies
                for (size_t i = 0; i < environment.getEntityCount(); ++i) {
                    Enemy* enemy = dynamic_cast<Enemy*>(environment.getEntity(i));
                    if (enemy && enemy->isAlive() && attack->isActive()) {
                        if (!attack->hasHit(enemy) && attack->checkCollision(enemy->getPosition(), enemy->getRadius())) {
                            enemy->takeDamage(attack->getDamage());
                            attack->markHit(enemy);
                            attack->deactivate();
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

            // Remove dead entities
            environment.removeDeadEntities();
        }

        // Rendering
        window.clear(sf::Color(30, 30, 40));

        if (gameState == MenuState::MAIN_MENU || gameState == MenuState::CLASS_SELECT) {
            menu.draw(window);
        } else if (gameState == MenuState::LEADERBOARD) {
            leaderboard.draw(window, font);
        } else if (gameState == MenuState::PLAYING && player) {
            player->draw(window);

            for (size_t i = 0; i < environment.getEntityCount(); ++i) {
                Enemy* enemy = dynamic_cast<Enemy*>(environment.getEntity(i));
                if (enemy && enemy->isAlive()) {
                    enemy->draw(window);
                }
            }

            for (auto& attack : attacks) {
                attack->draw(window);
            }

            hud.draw(window);
            
        } else if (gameState == MenuState::PAUSED) {
            if (player) {
                player->draw(window);
            }
            
            for (size_t i = 0; i < environment.getEntityCount(); ++i) {
                Enemy* enemy = dynamic_cast<Enemy*>(environment.getEntity(i));
                if (enemy && enemy->isAlive()) {
                    enemy->draw(window);
                }
            }
            
            for (auto& attack : attacks) {
                attack->draw(window);
            }
            
            sf::RectangleShape overlay(sf::Vector2f(1280, 720));
            overlay.setFillColor(sf::Color(0, 0, 0, 180));
            window.draw(overlay);
            
            sf::Text pauseText;
            pauseText.setFont(font);
            pauseText.setString("PAUSED");
            pauseText.setCharacterSize(80);
            pauseText.setFillColor(sf::Color::White);
            pauseText.setStyle(sf::Text::Bold);
            sf::FloatRect bounds = pauseText.getLocalBounds();
            pauseText.setOrigin(bounds.width / 2, bounds.height / 2);
            pauseText.setPosition(640, 250);
            window.draw(pauseText);
            
            sf::Text instructions;
            instructions.setFont(font);
            instructions.setString("ESC - Resume\nR - Restart\nQ - Quit to Menu");
            instructions.setCharacterSize(40);
            instructions.setFillColor(sf::Color(200, 200, 200));
            sf::FloatRect instrBounds = instructions.getLocalBounds();
            instructions.setOrigin(instrBounds.width / 2, instrBounds.height / 2);
            instructions.setPosition(640, 400);
            window.draw(instructions);
            
        } else if (gameState == MenuState::GAME_OVER) {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setString("GAME OVER");
            gameOverText.setCharacterSize(80);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setStyle(sf::Text::Bold);
            sf::FloatRect bounds = gameOverText.getLocalBounds();
            gameOverText.setOrigin(bounds.width / 2, bounds.height / 2);
            gameOverText.setPosition(640, 250);
            window.draw(gameOverText);
            
            // Only draw stats if player still exists
            if (player) {
                sf::Text statsText;
                statsText.setFont(font);
                statsText.setString("Wave: " + std::to_string(waveManager.getCurrentWave()) + "\n" +
                                   "Kills: " + std::to_string(player->getKills()) + "\n" +
                                   "Level: " + std::to_string(player->getLevel()));
                statsText.setCharacterSize(40);
                statsText.setFillColor(sf::Color::White);
                sf::FloatRect statsBounds = statsText.getLocalBounds();
                statsText.setOrigin(statsBounds.width / 2, statsBounds.height / 2);
                statsText.setPosition(640, 380);
                window.draw(statsText);
            }
            
            sf::Text instructions;
            instructions.setFont(font);
            instructions.setString("R - Restart\nESC/Q - Main Menu");
            instructions.setCharacterSize(30);
            instructions.setFillColor(sf::Color(150, 150, 150));
            sf::FloatRect instrBounds = instructions.getLocalBounds();
            instructions.setOrigin(instrBounds.width / 2, instrBounds.height / 2);
            instructions.setPosition(640, 520);
            window.draw(instructions);
        }

        window.display();
    }

    // Cleanup
    if (player) delete player;
    for (size_t i = 0; i < environment.getEntityCount(); ++i) {
        delete environment.getEntity(i);
    }
    environment.clearEntities();

    return 0;
}