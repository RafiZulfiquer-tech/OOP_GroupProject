#include "SFML/Graphics.hpp"
#include "environment.h"
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
    MenuState gameState = MenuState::MAIN_MENU;
    sf::Clock clock;

    std::cout << "Game started! Use mouse to navigate menus." << std::endl;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            // All menu, state, input and render logic here
            // (Copy complete logic as shown originally)
        }

        // All game state updates and rendering here
        // (Copy complete logic as shown originally)
    }

    if (player) delete player;
    for (auto enemy : enemies) delete enemy;
    return 0;
}
