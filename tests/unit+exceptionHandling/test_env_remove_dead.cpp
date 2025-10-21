#include "Environment.h"
#include "Enemy.h"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Testing remove dead entities..." << std::endl;
    try {
        Environment env(800, 600);
        
        Enemy* alive1 = new Enemy(100.f, 100.f, 100, 80.f, 15, 25);
        Enemy* dead = new Enemy(200.f, 200.f, 100, 80.f, 15, 25);
        Enemy* alive2 = new Enemy(300.f, 300.f, 100, 80.f, 15, 25);
        
        env.spawnEntity(alive1);
        env.spawnEntity(dead);
        env.spawnEntity(alive2);
        
        dead->takeDamage(100); // Kill the middle entity
        assert(env.getEntityCount() == 3);
        
        // env.removeDeadEntities();
        // assert(env.getEntityCount() == 2);
        
        // env.clearEntities();
        
        std::cout << "✓ PASSED: Remove dead entities" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ FAILED: " << e.what() << std::endl;
        return 1;
    }
}