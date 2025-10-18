#include "../../Warrior.h"
#include "../../Goblin.h"
#include "../../environment.h"
#include <iostream>

int main() {
    std::cout << "Testing wave survival..." << std::endl;
    
    Environment env(800, 600);
    Warrior* player = new Warrior(400.f, 300.f);
    env.spawnEntity(player);
    
    // Wave 1: 3 goblins
    for (int i = 0; i < 3; i++) {
        Goblin* goblin = new Goblin(400.f + i*50.f, 200.f);
        env.spawnEntity(goblin);
    }
    
    if (env.getEntityCount() != 4) {
        std::cout << "FAIL: Should have player + 3 goblins" << std::endl;
        return 1;
    }
    
    // Kill all wave 1 enemies
    for (size_t i = 1; i < env.getEntityCount(); ) {
        Entity* entity = env.getEntity(i);
        entity->takeDamage(100);
        if (!entity->isAlive()) {
            player->addXP(10);
            player->addKill();
        }
        i++;
    }
    
    env.removeDeadEntities();
    
    if (env.getEntityCount() != 1) {
        std::cout << "FAIL: Only player should remain" << std::endl;
        return 1;
    }
    
    if (player->getKills() != 3) {
        std::cout << "FAIL: Should have 3 kills" << std::endl;
        return 1;
    }
    
    if (player->getXP() != 30) {
        std::cout << "FAIL: Should have 30 XP" << std::endl;
        return 1;
    }
    
    env.clearEntities();
    std::cout << "PASS: Wave survival test passed!" << std::endl;
    return 0;
}
