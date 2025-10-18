#include "../../environment.h"
#include "../../Warrior.h"
#include "../../Goblin.h"
#include <iostream>

int main() {
    std::cout << "Testing collision detection..." << std::endl;
    
    Environment env(800, 600);
    
    Warrior* player = new Warrior(100.f, 100.f);
    Goblin* nearEnemy = new Goblin(115.f, 100.f);  // Close
    Goblin* farEnemy = new Goblin(500.f, 500.f);   // Far
    
    env.spawnEntity(player);
    env.spawnEntity(nearEnemy);
    env.spawnEntity(farEnemy);
    
    // Close entities should collide
    if (!env.checkCollision(player, nearEnemy)) {
        std::cout << "FAIL: Close entities should collide" << std::endl;
        return 1;
    }
    
    // Far entities should NOT collide
    if (env.checkCollision(player, farEnemy)) {
        std::cout << "FAIL: Far entities should not collide" << std::endl;
        return 1;
    }
    
    // Test with null pointers (should not crash)
    if (env.checkCollision(nullptr, player)) {
        std::cout << "FAIL: Null check failed" << std::endl;
        return 1;
    }
    
    env.clearEntities();
    std::cout << "PASS: Collision test passed!" << std::endl;
    return 0;
}
