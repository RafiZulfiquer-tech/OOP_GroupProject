#include "GoblinBrute.h"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Testing GoblinBrute armor reduction..." << std::endl;
    try {
        GoblinBrute brute(0.f, 0.f);
        
        int initialHealth = brute.getHealth();
        
        // Take 20 damage with 10 armor: should take max(1, 20-10) = 10 damage
        brute.takeDamage(20);
        assert(brute.getHealth() == initialHealth - 10);
        
        // Armor should reduce by 1 each hit
        // Next hit: 20 damage with 9 armor: should take max(1, 20-9) = 11 damage
        brute.takeDamage(20);
        assert(brute.getHealth() == initialHealth - 10 - 11);
        
        std::cout << "✓ PASSED: GoblinBrute armor reduction" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ FAILED: " << e.what() << std::endl;
        return 1;
    }
}