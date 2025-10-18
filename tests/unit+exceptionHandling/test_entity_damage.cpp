#include "Entity.h"
#include "Enemy.h"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Testing Entity takeDamage..." << std::endl;
    try {
        Enemy entity(0.f, 0.f, 100, 80.f, 15, 25);
        
        // Normal damage
        entity.takeDamage(30);
        assert(entity.getHealth() == 70);
        assert(entity.isAlive() == true);
        
        // Damage that kills
        entity.takeDamage(80);
        assert(entity.getHealth() == 0);
        assert(entity.isAlive() == false);
        
        std::cout << "✓ PASSED: Entity takeDamage" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ FAILED: " << e.what() << std::endl;
        return 1;
    }
}