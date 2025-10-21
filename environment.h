#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <stdexcept>

class Entity; // Forward declaration

class Environment {
public:
    Environment(int width, int height);

    void spawnEntity(Entity* entity);
    void removeEntity(Entity* entity);
    bool checkCollision(Entity* a, Entity* b) const;
    void clampPosition(int& x, int& y) const;
    int getWidth() const;
    int getHeight() const;
    size_t getEntityCount() const;
    Entity* getEntity(size_t index) const { return entities.at(index); }
    void clearEntities();
    void removeDeadEntities();

private:
    int width, height;  
    std::vector<Entity*> entities;
};

#endif // ENVIRONMENT_H
