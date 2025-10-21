#ifndef ROGUE_H
#define ROGUE_H

#include "Player.h"

// Rogue class inherits from Player, specializing attack behavior and visuals
class Rogue : public Player {
protected:
    float daggerSpeed;   // Speed at which daggers are thrown
    int daggerDamage;    // Base damage per dagger attack
    float critChance;    // Probability of critical hit (double damage)

public:
    Rogue(float x, float y);  // Constructor: initialize position and Rogue-specific stats

    // Override createAttack to produce a dagger attack aimed at a given angle
    std::unique_ptr<Attack> createAttack(float angleToMouse) override;

    // Override evolve to mark Rogue as evolved (could add more effects later)
    void evolve() override;

    // Getter for critical hit chance
    float getCritChance() const;

    // Calculate attack damage with a chance for critical hit
    int calculateDamage() const;

    // Override draw to render Rogue with unique colors and style
    void draw(sf::RenderWindow& window) override;
};

#endif // ROGUE_H