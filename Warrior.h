#ifndef WARRIOR_H
#define WARRIOR_H

#include "Player.h"

class Warrior : public Player {
protected:
    float meleeDamage;
    float meleeRange;
public:
    Warrior(float x, float y);
    std::unique_ptr<Attack> createAttack(float angleToMouse) override;
    void evolve() override;
    float getMeleeDamage() const;
    float getMeleeRange() const;
    // change colour of character
    void draw(sf::RenderWindow& window) override;
};

#endif // WARRIOR_H
