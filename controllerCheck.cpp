#include <SFML/Graphics.hpp>
#include "Controller.h"
#include <cmath>
#include <vector>

// Simple visual for player attacks
class AttackAnimation {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    float angle;
    float lifetime;
    float maxLifetime;
    bool alive;

public:
    AttackAnimation(sf::Vector2f pos, float ang) 
        : position(pos), angle(ang), lifetime(0.f), maxLifetime(0.3f), alive(true) {
        
        // Circle representing attack projectile
        shape.setRadius(8.f);
        shape.setOrigin(8.f, 8.f);
        shape.setFillColor(sf::Color::Yellow);
        shape.setOutlineColor(sf::Color::Red);
        shape.setOutlineThickness(2.f);
    }

    void update(float deltaTime) {
        if (!alive) return;

        lifetime += deltaTime;
        
        // Move projectile forward by speed and angle
        float speed = 500.f;
        float radians = angle * 3.14159265f / 180.f;
        position.x += std::cos(radians) * speed * deltaTime;
        position.y += std::sin(radians) * speed * deltaTime;

        // Fade out over lifetime
        float alpha = 1.f - (lifetime / maxLifetime);
        sf::Color color = shape.getFillColor();
        color.a = static_cast<sf::Uint8>(255 * alpha);
        shape.setFillColor(color);

        shape.setPosition(position);

        // Mark dead after max lifetime
        if (lifetime >= maxLifetime) {
            alive = false;
        }
    }

    void draw(sf::RenderWindow& window) {
        if (alive) {
            window.draw(shape);
        }
    }

    bool isAlive() const { return alive; }
};

int main() {
    // Setup window and frame rate
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Controller Demo");
    window.setFramerateLimit(60);

    Controller controller;

    // Player setup (circle)
    sf::CircleShape player(30.f);
    player.setOrigin(30.f, 30.f);
    player.setFillColor(sf::Color::Cyan);
    player.setOutlineColor(sf::Color::White);
    player.setOutlineThickness(3.f);

    sf::Vector2f playerPos(640.f, 360.f);
    float playerSpeed = 300.f;
    float playerRotation = 0.f;

    // Arrow to indicate facing direction
    sf::RectangleShape directionArrow(sf::Vector2f(40.f, 4.f));
    directionArrow.setOrigin(0.f, 2.f);
    directionArrow.setFillColor(sf::Color::White);

    // Store active attack animations
    std::vector<AttackAnimation> attacks;

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Pass input events to controller
            controller.handleEvent(event);
        }

        // Update mouse position in controller
        controller.update(window);

        // Move player based on WASD input
        sf::Vector2f moveVec = controller.getMoveVector();
        playerPos.x += moveVec.x * playerSpeed * deltaTime;
        playerPos.y += moveVec.y * playerSpeed * deltaTime;

        // Clamp player position inside window bounds
        if (playerPos.x < 30.f) playerPos.x = 30.f;
        if (playerPos.x > 1250.f) playerPos.x = 1250.f;
        if (playerPos.y < 30.f) playerPos.y = 30.f;
        if (playerPos.y > 690.f) playerPos.y = 690.f;

        // Rotate player to face mouse
        playerRotation = controller.getMouseAngle(playerPos);

        // Trigger attack animation on left click
        if (controller.isAttackPressed()) {
            attacks.push_back(AttackAnimation(playerPos, playerRotation));
            player.setFillColor(sf::Color::Red); // flash red when attacking
        } else {
            player.setFillColor(sf::Color::Cyan); // normal color
        }

        // Update all attack animations
        for (auto& attack : attacks) {
            attack.update(deltaTime);
        }

        // Remove finished attacks
        attacks.erase(
            std::remove_if(attacks.begin(), attacks.end(),
                [](const AttackAnimation& a) { return !a.isAlive(); }),
            attacks.end()
        );

        // --- Rendering ---
        window.clear(sf::Color(30, 30, 40));

        // Draw player
        player.setPosition(playerPos);
        player.setRotation(playerRotation);
        window.draw(player);

        // Draw facing direction arrow
        directionArrow.setPosition(playerPos);
        directionArrow.setRotation(playerRotation);
        window.draw(directionArrow);

        // Draw all active attacks
        for (auto& attack : attacks) {
            attack.draw(window);
        }

        // Draw instructions text if font loads
        sf::Font font;
        if (font.loadFromFile("arial.ttf")) {
            sf::Text instructions;
            instructions.setFont(font);
            instructions.setString("WASD - Move | Left Click - Attack");
            instructions.setCharacterSize(24);
            instructions.setFillColor(sf::Color::White);
            instructions.setPosition(10, 10);
            window.draw(instructions);
        }

        window.display();
    }

    return 0;
}