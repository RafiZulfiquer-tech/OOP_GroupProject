#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Enemy : public Entity {
protected:
    float speed;              // Movement speed
    int damage;               // Damage dealt per attack
    float attackCooldown;     // Time between attacks (seconds)
    float currentCooldown;    // Remaining cooldown time before next attack
    int xpReward;             // XP given to player on enemy death

public:
    Enemy(float x, float y, int hp, float spd, int dmg, int xp);
    virtual ~Enemy() = default;

    // Move enemy toward a target position
    virtual void moveToward(sf::Vector2f target, float dt);

    // Check if enemy can attack (cooldown expired & alive)
    virtual bool canAttack() const;

    // Get damage value
    virtual int getDamage() const;

    // Reset cooldown after attacking
    virtual void resetCooldown();

    // Update cooldown timer
    virtual void update(float dt) override;

    // Draw enemy on screen
    virtual void draw(sf::RenderWindow& window) override;

    // Get XP reward value
    int getXPReward() const { return xpReward; }
};

#endif // ENEMY_H