#ifndef GOBLIN_H
#define GOBLIN_H

#include "Enemy.h"

class Goblin : public Enemy {
public:
    Goblin(float x, float y);
    void draw(sf::RenderWindow& window) override;
};

#endif // GOBLIN_H
