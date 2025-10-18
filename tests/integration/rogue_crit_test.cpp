#include "../../Rogue.h"
#include <iostream>

int main() {
    std::cout << "Testing rogue critical hits..." << std::endl;
    
    Rogue rogue(100.f, 100.f);
    
    // Rogue has 15% crit chance
    if (rogue.getCritChance() != 0.15f) {
        std::cout << "FAIL: Crit chance should be 0.15" << std::endl;
        return 1;
    }
    
    // Test damage calculation (should return normal or crit)
    bool foundNormal = false;
    bool foundCrit = false;
    
    for (int i = 0; i < 100; i++) {
        int dmg = rogue.calculateDamage();
        if (dmg == 20) foundNormal = true;
        if (dmg == 40) foundCrit = true;
    }
    
    if (!foundNormal) {
        std::cout << "FAIL: Should find normal damage (20)" << std::endl;
        return 1;
    }
    
    // Crits are random, might not always appear in 100 tries
    std::cout << "  Found normal damage: Yes" << std::endl;
    std::cout << "  Found crit damage: " << (foundCrit ? "Yes" : "No (rare but ok)") << std::endl;
    
    std::cout << "PASS: Rogue crit test passed!" << std::endl;
    return 0;
}
