#include "../../environment.h"
#include "../../Enemy.h"
#include "../../Warrior.h"
#include <iostream>

int main() {
    std::cout << "Testing environment..." << std::endl;
    
    Environment env(800, 600);
    Enemy* e1 = new Enemy(100.f, 100.f, 50, 80.f, 15, 25);
    Enemy* e2 = new Enemy(200.f, 200.f, 50, 80.f, 15, 25);
    Warrior* p = new Warrior(300.f, 300.f);
    
    env.spawnEntity(e1);
    env.spawnEntity(e2);
    env.spawnEntity(p);
    
    if (env.getEntityCount() != 3) {
        std::cout << "FAIL: Wrong entity count" << std::endl;
        return 1;
    }
    
    e1->takeDamage(100);
    env.removeDeadEntities();
    
    if (env.getEntityCount() != 2) {
        std::cout << "FAIL: Dead entity not removed" << std::endl;
        return 1;
    }
    
    env.clearEntities();
    std::cout << "PASS: Environment test passed!" << std::endl;
    return 0;
}
