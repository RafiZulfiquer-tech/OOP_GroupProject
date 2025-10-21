#include "Enemy.h"
#include <cmath>
#include <algorithm>

// Constructor: initializes Enemy with position, health, speed, damage, and XP reward
Enemy::Enemy(float x, float y, int hp, float spd, int dmg, int xp)
    : Entity(x, y, 15.f, hp),   // Call base Entity constructor with radius 15
      speed(spd), damage(dmg),
      attackCooldown(1.f),      // Time (in seconds) between attacks
      currentCooldown(0.f),     // Current time left until next attack allowed
      xpReward(xp) {}

// Moves enemy toward a target position, scaled by delta time for smooth movement
void Enemy::moveToward(sf::Vector2f target, float dt) {
    sf::Vector2f direction = target - position;   // Vector pointing toward target
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) {
        direction /= length;                       // Normalize direction vector
        position += direction * speed * dt;       // Move enemy along direction
    }
}

// Returns whether enemy can perform an attack (cooldown expired and alive)
bool Enemy::canAttack() const { return currentCooldown <= 0.f && alive; }

// Returns the damage this enemy inflicts
int Enemy::getDamage() const { return damage; }

// Resets attack cooldown timer after an attack
void Enemy::resetCooldown() { currentCooldown = attackCooldown; }

// Updates cooldown timer each frame by subtracting delta time
void Enemy::update(float dt) {
    if (currentCooldown > 0) {
        currentCooldown -= dt;
        if (currentCooldown < 0) currentCooldown = 0; // Clamp to zero
    }
}

// Draw enemy as a red circle at its current position, only if alive
void Enemy::draw(sf::RenderWindow& window) {
    if (!alive) return;    // Don't draw dead enemies
    sf::CircleShape shape(radius);
    // Position shape centered on enemy position
    shape.setPosition(position.x - radius, position.y - radius);
    shape.setFillColor(sf::Color::Red);
    window.draw(shape);
}