#include "Environment.h"
#include <algorithm>

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
    // Placeholder: Assume Entity has x, y, radius
    if (!a || !b) return false;
    int dx = a->getX() - b->getX();
    int dy = a->getY() - b->getY();
    int distSq = dx * dx + dy * dy;
    int radSum = a->getRadius() + b->getRadius();
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
