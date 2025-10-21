#include "Environment.h"
#include "Entity.h"
#include <algorithm>
#include <cmath>

Environment::Environment(int width, int height)
    : width(width), height(height) {}

// Add entity to environment
void Environment::spawnEntity(Entity* entity) {
    if (!entity) throw std::invalid_argument("Null entity cannot be spawned");
    entities.push_back(entity);
}

// Remove entity if found
void Environment::removeEntity(Entity* entity) {
    auto it = std::remove(entities.begin(), entities.end(), entity);
    if (it != entities.end()) {
        entities.erase(it, entities.end());
    } else {
        throw std::runtime_error("Entity not found in environment");
    }
}

// Check circle collision between two entities
bool Environment::checkCollision(Entity* a, Entity* b) const {
    if (!a || !b) return false;

    sf::Vector2f posA = a->getPosition();
    sf::Vector2f posB = b->getPosition();

    float dx = posA.x - posB.x;
    float dy = posA.y - posB.y;
    float distSq = dx * dx + dy * dy;

    float radSum = a->getRadius() + b->getRadius();
    return distSq <= radSum * radSum;
}

// Clamp position to environment bounds
void Environment::clampPosition(int& x, int& y) const {
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > width) x = width;
    if (y > height) y = height;
}

// Delete and clear all entities
void Environment::clearEntities() {
    for (auto entity : entities) {
        delete entity;
    }
    entities.clear();
}

// Remove and delete dead entities
void Environment::removeDeadEntities() {
    entities.erase(
        std::remove_if(entities.begin(), entities.end(),
            [](Entity* e) {
                if (!e->isAlive()) {
                    delete e;
                    return true;
                }
                return false;
            }),
        entities.end()
    );
}

// Getters
int Environment::getWidth() const { return width; }
int Environment::getHeight() const { return height; }
size_t Environment::getEntityCount() const { return entities.size(); }