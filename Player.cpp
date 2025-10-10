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

    // Keep in bounds (adjust these to match your window size)
    if (position.x < radius) position.x = radius;
    if (position.x > 1280 - radius) position.x = 1280 - radius;
    if (position.y < radius) position.y = radius;
    if (position.y > 720 - radius) position.y = 720 - radius;
  }
}

bool Player::canAttack() const { 
  return currentCooldown <= 0.f; 
}

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

void Player::addKill() { 
  kills++; 
}

int Player::getLevel() const { 
  return level; 
}

int Player::getXP() const { 
  return xp; 
}

int Player::getKills() const { 
  return kills; 
}

std::string Player::getClassName() const { 
  return className; 
}

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
  
  // Optional: Draw health bar
  float healthPercent = static_cast<float>(health) / static_cast<float>(maxHealth);
  sf::RectangleShape healthBarBg(sf::Vector2f(radius * 2, 4.f));
  healthBarBg.setPosition(position.x - radius, position.y - radius - 8.f);
  healthBarBg.setFillColor(sf::Color(50, 50, 50));
  window.draw(healthBarBg);
  
  sf::RectangleShape healthBar(sf::Vector2f(radius * 2 * healthPercent, 4.f));
  healthBar.setPosition(position.x - radius, position.y - radius - 8.f);
  healthBar.setFillColor(sf::Color::Green);
  window.draw(healthBar);
}
