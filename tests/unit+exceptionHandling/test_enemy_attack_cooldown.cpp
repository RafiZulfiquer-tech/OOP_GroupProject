#include "Enemy.h"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Testing Enemy attack cooldown..." << std::endl;
    try {
        Enemy enemy(0.f, 0.f, 50, 100.f, 15, 25);
        
        assert(enemy.canAttack() == true);
        
        enemy.resetCooldown();
        assert(enemy.canAttack() == false);
        
        enemy.update(1.1f); // Wait for cooldown (1 second)
        assert(enemy.canAttack() == true);
        
        std::cout << "✓ PASSED: Enemy attack cooldown" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ FAILED: " << e.what() << std::endl;
        return 1;
    }
}