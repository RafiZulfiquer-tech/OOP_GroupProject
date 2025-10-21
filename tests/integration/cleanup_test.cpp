#include "../../Environment.h"
#include "../../Enemy.h"
#include "../../Goblin.h"
#include <iostream>

int main() {
    std::cout << "Testing entity cleanup..." << std::endl;
    
    Environment env(800, 600);
    
    // Spawn many entities
    for (int i = 0; i < 20; i++) {
        Enemy* enemy = new Enemy(i*40.f, 100.f, 50, 80.f, 15, 25);
        env.spawnEntity(enemy);
    }
    
    if (env.getEntityCount() != 20) {
        std::cout << "FAIL: Should have 20 entities" << std::endl;
        return 1;
    }
    
    // Kill half of them
    for (size_t i = 0; i < 10; i++) {
        env.getEntity(i)->takeDamage(100);
    }
    
    // Remove dead ones
    env.removeDeadEntities();
    
    if (env.getEntityCount() != 10) {
        std::cout << "FAIL: Should have 10 entities left" << std::endl;
        return 1;
    }
    
    // Clear all
    env.clearEntities();
    
    if (env.getEntityCount() != 0) {
        std::cout << "FAIL: Should have 0 entities" << std::endl;
        return 1;
    }
    
    std::cout << "PASS: Cleanup test passed!" << std::endl;
    return 0;
}
