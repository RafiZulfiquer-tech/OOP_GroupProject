#include "Environment.h"
#include "Entity.h"  // ← ADD THIS
#include <algorithm>
#include <cmath>

Environment::Environment(int width, int height) : width(width), height(height) {}

void Environment::spawnEntity(Entity* entity) {
    if (!entity) throw std::invalid_argument("Null entity cannot be spawned");
    entities.push_back(entity);
}

void Environment::removeEntity(Entity* entity) {
    auto it = std::remove(entities.begin(), entities.end(), entity);
    if (it != entities.end()) {
        entities.erase(it, entities.end());
    } else {
        throw std::runtime_error("Entity not found in environment");
    }
}

bool Environment::checkCollision(Entity* a, Entity* b) const {
    if (!a || !b) return false;
    
    // Get positions using getPosition() which returns sf::Vector2f
    sf::Vector2f posA = a->getPosition();
    sf::Vector2f posB = b->getPosition();
    
    // Calculate distance
    float dx = posA.x - posB.x;  // ← Use .x not getX()
    float dy = posA.y - posB.y;  // ← Use .y not getY()
    float distSq = dx * dx + dy * dy;
    
    // Check if circles overlap
    float radSum = a->getRadius() + b->getRadius();
    return distSq <= radSum * radSum;
}

void Environment::clampPosition(int& x, int& y) const {
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > width) x = width;
    if (y > height) y = height;
}

int Environment::getWidth() const { return width; }
int Environment::getHeight() const { return height; }
size_t Environment::getEntityCount() const { return entities.size(); }