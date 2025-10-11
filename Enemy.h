#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity {
private:
    float speed;
    int damage;
    float attackCooldown;
    float currentCooldown;

public:
    Enemy(float x, float y, int hp, float spd, int dmg);

    void moveToward(sf::Vector2f target, float dt);
    bool canAttack() const;
    int getDamage() const;
    void resetCooldown();

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};

#endif
