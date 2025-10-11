#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
 protected:
  sf::Vector2f position;
  float radius;
  int health;
  int maxHealth;
  bool alive;

 public:
  Entity(float x, float y, float r, int hp);
  virtual ~Entity();

  sf::Vector2f getPosition() const;
  float getRadius() const;
  bool isAlive() const;
  int getHealth() const;
  int getMaxHealth() const;

  virtual void takeDamage(int damage);
  virtual void update(float dt) = 0;
  virtual void draw(sf::RenderWindow& window) = 0;
};

#endif