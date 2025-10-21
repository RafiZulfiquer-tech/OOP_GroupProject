#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <stdexcept>

class Entity; // Forward declaration

class Environment {
public:
    Environment(int width, int height);

    void spawnEntity(Entity* entity);          // Add entity to environment
    void removeEntity(Entity* entity);         // Remove specific entity
    bool checkCollision(Entity* a, Entity* b) const;  // Check overlap
    void clampPosition(int& x, int& y) const;  // Keep position within bounds

    int getWidth() const;
    int getHeight() const;
    size_t getEntityCount() const;
    Entity* getEntity(size_t index) const { return entities.at(index); }

    void clearEntities();        // Delete all entities
    void removeDeadEntities();   // Delete and remove dead ones

private:
    int width, height;
    std::vector<Entity*> entities;
};

#endif // ENVIRONMENT_H