#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>

// Handles player input: movement, mouse, and attack
class Controller {
private:
    bool attackPressed;         // Tracks if attack button was pressed
    sf::Vector2f mousePosition; // Current mouse position in world coords

public:
    Controller();

    // Update mouse position each frame
    void update(sf::RenderWindow &window);

    // Process input events (e.g., mouse clicks)
    void handleEvent(const sf::Event &event);

    // Get normalized movement vector from WASD keys
    sf::Vector2f getMoveVector() const;

    // Check if attack was pressed, reset after reading
    bool isAttackPressed();

    // Get current mouse position in world coordinates
    sf::Vector2f getMousePosition() const { return mousePosition; }

    // Calculate angle (degrees) from given point to mouse
    float getMouseAngle(sf::Vector2f fromPosition) const;
};

#endif