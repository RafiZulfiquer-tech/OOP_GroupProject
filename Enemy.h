#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Enemy : public Entity {
protected:
    float speed;
    int damage;
    float attackCooldown;
    float currentCooldown;
    int xpReward;
public:
    Enemy(float x, float y, int hp, float spd, int dmg, int xp);
    virtual ~Enemy() = default;

    virtual void moveToward(sf::Vector2f target, float dt);
    virtual bool canAttack() const;
    virtual int getDamage() const;
    virtual void resetCooldown();
    virtual void update(float dt) override;
    virtual void draw(sf::RenderWindow& window) override;
    int getXPReward() const { return xpReward; }
};

#endif // ENEMY_H
