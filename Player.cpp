#include "Player.h"

#include <cmath>

Player::Player(float x, float y)
    : Entity(x, y, 20.f, 100),
      speed(200.f),
      xp(0),
      level(1),
      kills(0),
      attackCooldown(0.5f),
      currentCooldown(0.f),
      className("Warrior") {}

void Player::move(sf::Vector2f direction, float dt) {
  if (direction.x != 0 || direction.y != 0) {
    float length =
        std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction.x /= length;
    direction.y /= length;

    position.x += direction.x * speed * dt;
    position.y += direction.y * speed * dt;

    // Keep in bounds
    if (position.x < radius) position.x = radius;
    if (position.x > 800 - radius) position.x = 800 - radius;
    if (position.y < radius) position.y = radius;
    if (position.y > 600 - radius) position.y = 600 - radius;
  }
}

bool Player::canAttack() const { return currentCooldown <= 0.f; }

void Player::attack() {
  if (canAttack()) {
    currentCooldown = attackCooldown;
  }
}

void Player::addXP(int amount) {
  xp += amount;
  int xpNeeded = level * 100;
  if (xp >= xpNeeded) {
    level++;
    xp -= xpNeeded;
    maxHealth += 20;
    health = maxHealth;
    speed += 10.f;
    attackCooldown *= 0.9f;
  }
}

void Player::addKill() { kills++; }

int Player::getLevel() const { return level; }
int Player::getXP() const { return xp; }
int Player::getKills() const { return kills; }
std::string Player::getClassName() const { return className; }

void Player::update(float dt) {
  if (currentCooldown > 0) {
    currentCooldown -= dt;
  }
}

void Player::draw(sf::RenderWindow& window) {
  sf::CircleShape shape(radius);
  shape.setPosition(position.x - radius, position.y - radius);
  shape.setFillColor(sf::Color::Green);
  shape.setOutlineThickness(2.f);
  shape.setOutlineColor(sf::Color::White);
  window.draw(shape);
  // Health bar etc. can be added here
}
