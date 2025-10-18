#include "Player.h"
#include "Warrior.h"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Testing Player movement..." << std::endl;
    try {
        Warrior player(100.f, 100.f);
        
        sf::Vector2f moveDir(1.f, 0.f);
        player.move(moveDir, 1.f); // Move right for 1 second
        
        assert(player.getPosition().x == 200.f); // Should move 100 units
        assert(player.getPosition().y == 100.f);
        
        std::cout << "✓ PASSED: Player movement" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ FAILED: " << e.what() << std::endl;
        return 1;
    }
}