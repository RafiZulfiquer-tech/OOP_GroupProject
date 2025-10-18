#ifndef GOBLINBRUTE_H
#define GOBLINBRUTE_H

#include "Enemy.h"

class GoblinBrute : public Enemy {
private:
    int armor;
    int baseArmor;
public:
    GoblinBrute(float x, float y, float hp = 120, float speed = 60.f, float damage = 20);
    void takeDamage(int dmg) override;
    void draw(sf::RenderWindow& window) override;
};

#endif // GOBLINBRUTE_H
