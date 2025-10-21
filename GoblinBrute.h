#ifndef GOBLINBRUTE_H
#define GOBLINBRUTE_H

#include "Enemy.h"

// Tanky goblin with armor that reduces incoming damage
class GoblinBrute : public Enemy {
private:
    int armor;       // Current armor value
    int baseArmor;   // Starting armor value

public:
    GoblinBrute(float x, float y, float hp = 120, float speed = 60.f, float damage = 20);
    
    void takeDamage(int dmg) override;        // Apply armor-based damage reduction
    void draw(sf::RenderWindow& window) override; // Draw with armor visuals
};

#endif // GOBLINBRUTE_H