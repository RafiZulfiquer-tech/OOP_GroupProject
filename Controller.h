#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>

// initiate class
class Controller {
    private: 
    bool attackPressed;
    sf::Vector2f mousePosition;

    public:
    Controller();


    //update input state
    void update(sf::RenderWindow &window);  
    void handleEvent(const sf::Event &event);

    //movement (WASD)
    sf::Vector2f getMoveVector() const;

    //Attack
    bool isAttackPressed();

    //mouse
    sf::Vector2f getMousePosition() const {return mousePosition;}
    float getMouseAngle(sf::Vector2f fromPosition) const;
};

#endif