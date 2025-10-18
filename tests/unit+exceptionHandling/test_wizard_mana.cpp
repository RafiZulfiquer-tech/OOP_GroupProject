#include "Rogue.h"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Testing Rogue critical hits..." << std::endl;
    try {
        Rogue rogue(0.f, 0.f);
        
        assert(rogue.getClassName() == "Rogue");
        assert(rogue.getCritChance() == 0.15f);
        
        // Test that calculateDamage returns valid values
        bool foundNormal = false;
        
        for (int i = 0; i < 100; i++) {
            int dmg = rogue.calculateDamage();
            // Should be either 20 (normal) or 40 (crit)
            assert(dmg == 20 || dmg == 40);
            if (dmg == 20) foundNormal = true;
        }
        
        // Should find normal damage (statistically very likely in 100 tries)
        assert(foundNormal == true);
        
        std::cout << "✓ PASSED: Rogue critical hits" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ FAILED: " << e.what() << std::endl;
        return 1;
    }
}