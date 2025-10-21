#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

// Base class for all game entities (players, enemies, etc.)
class Entity {
 protected:
  sf::Vector2f position;  // Current position
  float radius;           // Collision radius
  int health;             // Current health
  int maxHealth;          // Max health
  bool alive;             // Alive status

 public:
  Entity(float x, float y, float r, int hp);
  virtual ~Entity();

  // Basic getters
  sf::Vector2f getPosition() const;
  float getRadius() const;
  bool isAlive() const;
  int getHealth() const;
  int getMaxHealth() const;

  // Damage handling
  virtual void takeDamage(int damage);

  // Must be implemented by subclasses
  virtual void update(float dt) = 0;
  virtual void draw(sf::RenderWindow& window) = 0;
};

#endif