#ifndef GOBLIN_H
#define GOBLIN_H

#include "Enemy.h"

class Goblin : public Enemy {
public:
    Goblin(float x, float y, float hp = 50, float speed = 80.f, float damage = 10);
    void draw(sf::RenderWindow& window) override;
};

#endif // GOBLIN_H
