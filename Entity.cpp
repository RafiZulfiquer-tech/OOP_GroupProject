#include "Entity.h"

Entity::Entity(float x, float y, float r, int hp) {
    position = sf::Vector2f(x, y); // Set initial position
    radius = r;                    // Set entity size (collision radius)
    health = hp;                   // Set current health
    maxHealth = hp;                // Set max health
    alive = true;                  // Entity starts alive
}

Entity::~Entity() {}

sf::Vector2f Entity::getPosition() const { return position; }
float Entity::getRadius() const { return radius; }

// Check if entity is alive (health > 0 and alive flag true)
bool Entity::isAlive() const { return alive && health > 0; }

int Entity::getHealth() const { return health; }
int Entity::getMaxHealth() const { return maxHealth; }

// Reduce health by damage, mark dead if health <= 0
void Entity::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        health = 0;
        alive = false;
    }
}