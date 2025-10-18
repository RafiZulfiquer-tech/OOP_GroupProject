#include "Enemy.h"
#include <cassert>
#include <iostream>
#include <cmath>

int main() {
    std::cout << "Testing Enemy moveToward..." << std::endl;
    try {
        Enemy enemy(0.f, 0.f, 50, 100.f, 15, 25);
        
        sf::Vector2f initialPos = enemy.getPosition();
        sf::Vector2f target(100.f, 0.f);
        
        enemy.moveToward(target, 1.f); // Move for 1 second
        
        sf::Vector2f newPos = enemy.getPosition();
        
        // Should move 100 units toward target
        assert(newPos.x > initialPos.x);
        assert(std::abs(newPos.y - initialPos.y) < 0.01f); // Y should not change
        
        std::cout << "✓ PASSED: Enemy moveToward" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ FAILED: " << e.what() << std::endl;
        return 1;
    }
}