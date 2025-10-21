#include "../../Warrior.h"
#include "../../Goblin.h"
#include "../../Environment.h"
#include <iostream>

int main() {
    std::cout << "Testing combat..." << std::endl;
    
    Environment env(800, 600);
    Warrior* player = new Warrior(100.f, 100.f);
    Goblin* enemy = new Goblin(100.f, 100.f);
    
    env.spawnEntity(player);
    env.spawnEntity(enemy);
    
    if (!env.checkCollision(player, enemy)) {
        std::cout << "FAIL: Should collide" << std::endl;
        return 1;
    }
    
    int oldHealth = enemy->getHealth();
    enemy->takeDamage(20);
    
    if (enemy->getHealth() >= oldHealth) {
        std::cout << "FAIL: Health should decrease" << std::endl;
        return 1;
    }
    
    player->addXP(10);
    player->addKill();
    
    env.clearEntities();
    std::cout << "PASS: Combat test passed!" << std::endl;
    return 0;
}
