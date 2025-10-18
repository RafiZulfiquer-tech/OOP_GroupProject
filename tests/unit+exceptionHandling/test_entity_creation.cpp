#include "Entity.h"
#include "Enemy.h"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Testing Entity creation..." << std::endl;
    try {
        // Use Enemy since Entity is abstract
        Enemy entity(100.f, 200.f, 100, 80.f, 15, 25);
        
        assert(entity.getPosition().x == 100.f);
        assert(entity.getPosition().y == 200.f);
        assert(entity.getRadius() == 15.f);
        assert(entity.getHealth() == 100);
        assert(entity.getMaxHealth() == 100);
        assert(entity.isAlive() == true);
        
        std::cout << "✓ PASSED: Entity creation" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ FAILED: " << e.what() << std::endl;
        return 1;
    }
}