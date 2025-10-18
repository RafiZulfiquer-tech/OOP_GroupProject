#include "Warrior.h"
#include "Enemy.h"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Testing combat scenario (Player vs Enemy)..." << std::endl;
    try {
        Warrior* player = new Warrior(100.f, 100.f);
        Enemy* enemy = new Enemy(150.f, 150.f, 50, 80.f, 15, 25);
        
        int initialEnemyHealth = enemy->getHealth();
        
        // Enemy takes damage
        enemy->takeDamage(20);
        assert(enemy->getHealth() == initialEnemyHealth - 20);
        assert(enemy->isAlive() == true);
        
        // Kill enemy
        enemy->takeDamage(50);
        assert(enemy->isAlive() == false);
        
        // Player gains XP and kill (xpReward is public member)
        player->addXP(25);
        player->addKill();
        
        assert(player->getXP() == 25);
        assert(player->getKills() == 1);
        
        delete player;
        delete enemy;
        
        std::cout << "✓ PASSED: Combat scenario" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ FAILED: " << e.what() << std::endl;
        return 1;
    }
}