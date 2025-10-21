#include "Environment.h"
#include "Enemy.h"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Testing collision detection..." << std::endl;
    try {
        Environment env(800, 600);
        Enemy* e1 = new Enemy(100.f, 100.f, 100, 80.f, 15, 25);
        Enemy* e2 = new Enemy(110.f, 110.f, 100, 80.f, 15, 25);
        Enemy* e3 = new Enemy(200.f, 200.f, 100, 80.f, 15, 25);
        
        // Entities close together should collide
        assert(env.checkCollision(e1, e2) == true);
        
        // Entities far apart should not collide
        assert(env.checkCollision(e1, e3) == false);
        
        delete e1;
        delete e2;
        delete e3;
        
        std::cout << "✓ PASSED: Collision detection" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ FAILED: " << e.what() << std::endl;
        return 1;
    }
}