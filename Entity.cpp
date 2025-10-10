#include "Entity.h"

Entity::Entity(float x, float y, float r, int hp) {
  this->position = sf::Vector2f(x, y);
  this->radius = r;
  this->health = hp;
  this->maxHealth = hp;
  this->alive = true;
}

Entity::~Entity() {}

sf::Vector2f Entity::getPosition() const { return position; }
float Entity::getRadius() const { return radius; }
bool Entity::isAlive() const { return alive && health > 0; }
int Entity::getHealth() const { return health; }
int Entity::getMaxHealth() const { return maxHealth; }

void Entity::takeDamage(int damage) {
  health -= damage;
  if (health <= 0) {
    health = 0;
    alive = false;
  }
}
