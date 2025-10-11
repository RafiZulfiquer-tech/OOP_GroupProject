#include "Enemy.h"

#include <cmath>

Enemy::Enemy(float x, float y, int hp, float spd, int dmg)
    : Entity(x, y, 15.f, hp),
      speed(spd),
      damage(dmg),
      attackCooldown(1.f),
      currentCooldown(0.f) {}

void Enemy::moveToward(sf::Vector2f target, float dt) {
  sf::Vector2f direction = target - position;
  float length =
      std::sqrt(direction.x * direction.x + direction.y * direction.y);

  if (length > radius * 2) {
    direction.x /= length;
    direction.y /= length;
    position.x += direction.x * speed * dt;
    position.y += direction.y * speed * dt;
  }
}

bool Enemy::canAttack() const { return currentCooldown <= 0.f; }

int Enemy::getDamage() const { return damage; }

void Enemy::resetCooldown() { currentCooldown = attackCooldown; }

void Enemy::update(float dt) {
  if (currentCooldown > 0) {
    currentCooldown -= dt;
  }
}

void Enemy::draw(sf::RenderWindow& window) {
  sf::CircleShape shape(radius);
  shape.setPosition(position.x - radius, position.y - radius);
  shape.setFillColor(sf::Color::Red);
  shape.setOutlineThickness(2.f);
  shape.setOutlineColor(sf::Color(100, 0, 0));
  window.draw(shape);
  // Health bar etc. can be added here
}
