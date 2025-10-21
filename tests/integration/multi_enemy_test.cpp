#include "../../Warrior.h"
#include "../../Goblin.h"
#include "../../GoblinBrute.h"
#include "../../Environment.h"
#include <iostream>

int main() {
    std::cout << "Testing multiple enemy types..." << std::endl;
    
    Environment env(800, 600);
    
    Warrior* player = new Warrior(400.f, 300.f);
    Goblin* goblin = new Goblin(450.f, 300.f);
    GoblinBrute* brute = new GoblinBrute(350.f, 300.f);
    
    env.spawnEntity(player);
    env.spawnEntity(goblin);
    env.spawnEntity(brute);
    
    if (env.getEntityCount() != 3) {
        std::cout << "FAIL: Should have 3 entities" << std::endl;
        return 1;
    }
    
    // Goblin is weaker than brute
    if (goblin->getHealth() >= brute->getHealth()) {
        std::cout << "FAIL: Brute should have more health" << std::endl;
        return 1;
    }
    
    // Kill goblin first (easier)
    int goblinHP = goblin->getHealth();
    goblin->takeDamage(50);
    
    if (goblin->isAlive()) {
        std::cout << "FAIL: Goblin should be dead" << std::endl;
        return 1;
    }
    
    // Brute takes less damage due to armor
    int bruteHP = brute->getHealth();
    brute->takeDamage(50);
    int damageTaken = bruteHP - brute->getHealth();
    
    if (damageTaken >= 50) {
        std::cout << "FAIL: Brute armor should reduce damage" << std::endl;
        return 1;
    }
    
    env.clearEntities();
    std::cout << "PASS: Multi-enemy test passed!" << std::endl;
    return 0;
}
