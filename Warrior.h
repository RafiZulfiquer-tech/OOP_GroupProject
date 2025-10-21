#ifndef WARRIOR_H
#define WARRIOR_H

#include "Player.h"

// Warrior class inherits from Player and specializes in melee combat
class Warrior : public Player {
protected:
    float meleeDamage;  // Damage dealt by melee attacks
    float meleeRange;   // Range of melee attacks
public:
    // Constructor initializes position and warrior-specific stats
    Warrior(float x, float y);

    // Create a melee attack at a given angle
    std::unique_ptr<Attack> createAttack(float angleToMouse) override;

    // Handle evolution logic for the warrior
    void evolve() override;

    // Getters for melee damage and range
    float getMeleeDamage() const;
    float getMeleeRange() const;

    // Draw the warrior on the screen with unique appearance
    void draw(sf::RenderWindow& window) override;
};

#endif // WARRIOR_H