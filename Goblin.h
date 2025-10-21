#ifndef GOBLIN_H
#define GOBLIN_H

#include "Enemy.h"

// Basic enemy: Goblin
class Goblin : public Enemy {
public:
    // Constructor with default stats
    Goblin(float x, float y, float hp = 50, float speed = 80.f, float damage = 10);

    // Draw goblin on screen
    void draw(sf::RenderWindow& window) override;
};

#endif // GOBLIN_H