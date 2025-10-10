#include "Controller.h"
#include <cmath>    

Controller::Controller() : attackPressed(false) {}

void Controller::update(sf::RenderWindow& window) {
    //update mouse position
    sf:: Vector2i pixelPos = sf::Mouse::getPosition(window);
    mousePosition = window.mapPixelToCoords(pixelPos);
}
void Controller::handleEvent(const sf::Event& event) {
    //handle attack input pressed
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            attackPressed = true;
        }
    }
}

sf::Vector2f Controller::getMoveVector() const {
    sf::Vector2f moveVec(0.f,0.f);

    //WASD polling
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        moveVec.y -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        moveVec.y += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        moveVec.x -= 1.f;   
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        moveVec.x += 1.f;
    }

    // normalize diagonal movement
    if(moveVec.x != 0.f && moveVec.y != 0.f) {
        float length = std::sqrt(moveVec.x * moveVec.x + moveVec.y * moveVec.y);
        moveVec.x /= length;
        moveVec.y /= length;
    }
    return moveVec;

}
// Attack pressed check
bool Controller::isAttackPressed() {
    bool pressed = attackPressed;
    attackPressed = false; //reset after checking
    return pressed;
}

float Controller::getMouseAngle(sf::Vector2f fromPosition) const {
    float dx = mousePosition.x - fromPosition.x;
    float dy = mousePosition.y - fromPosition.y;
    return std::atan2(dy, dx) * 180.f / 3.14159f; // convert to degrees
}