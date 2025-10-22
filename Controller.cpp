#include "Controller.h"
#include <cmath>    

// initialise attack pressed to alse
Controller::Controller() : attackPressed(false) {}

// Update mouse position relative to the window in pixel coordinates
void Controller::update(sf::RenderWindow& window) {
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    mousePosition = window.mapPixelToCoords(pixelPos); //coordinates in game
}

// Handle mouse button press for attacks
void Controller::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            attackPressed = true;
        }
    }
}

// Get normalized movement vector from WASD keys
sf::Vector2f Controller::getMoveVector() const {
    sf::Vector2f moveVec(0.f, 0.f); //start at 0,0 not moving

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) moveVec.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) moveVec.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) moveVec.x -= 1.f;   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) moveVec.x += 1.f;

    // Normalize diagonal movement
    if (moveVec.x != 0.f && moveVec.y != 0.f) {
        float length = std::sqrt(moveVec.x * moveVec.x + moveVec.y * moveVec.y);
        moveVec.x /= length;
        moveVec.y /= length;
    }

    return moveVec;
}

// Check and reset attack press flag
bool Controller::isAttackPressed() {
    bool pressed = attackPressed;
    attackPressed = false;
    return pressed;
}

// Calculate angle (degrees) from a point to the mouse position
float Controller::getMouseAngle(sf::Vector2f fromPosition) const {
    float dx = mousePosition.x - fromPosition.x;
    float dy = mousePosition.y - fromPosition.y;
    return std::atan2(dy, dx) * 180.f / 3.14159f;
}