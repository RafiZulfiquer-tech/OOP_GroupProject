#include "Enemy.h"
#include <cmath>
#include <algorithm>

Enemy::Enemy(float x, float y, int hp, float spd, int dmg, int xp)
    : Entity(x, y, 15.f, hp), speed(spd), damage(dmg),
      attackCooldown(1.f), currentCooldown(0.f), xpReward(xp) {}

void Enemy::moveToward(sf::Vector2f target, float dt) {
    sf::Vector2f direction = target - position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) {
        direction /= length;
        position += direction * speed * dt;
    }
}

bool Enemy::canAttack() const { return currentCooldown <= 0.f && alive; }
int Enemy::getDamage() const { return damage; }
void Enemy::resetCooldown() { currentCooldown = attackCooldown; }

void Enemy::update(float dt) {
    if (currentCooldown > 0) {
        currentCooldown -= dt;
        if (currentCooldown < 0) currentCooldown = 0;
    }
}

void Enemy::draw(sf::RenderWindow& window) {
    if (!alive) return;
    sf::CircleShape shape(radius);
    shape.setPosition(position.x - radius, position.y - radius);
    shape.setFillColor(sf::Color::Red);
    window.draw(shape);
}
