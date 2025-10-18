#include "../../Warrior.h"
#include "../../Wizard.h"
#include "../../Rogue.h"
#include <iostream>

int main() {
    std::cout << "Testing player progression..." << std::endl;
    
    Warrior warrior(100.f, 100.f);
    
    // Start at level 1
    if (warrior.getLevel() != 1) {
        std::cout << "FAIL: Should start at level 1" << std::endl;
        return 1;
    }
    
    // Gain XP from killing enemies
    for (int i = 0; i < 10; i++) {
        warrior.addXP(10);  // Kill 10 goblins (10 XP each)
        warrior.addKill();
    }
    
    if (warrior.getXP() != 100) {
        std::cout << "FAIL: Should have 100 XP" << std::endl;
        return 1;
    }
    
    if (warrior.getKills() != 10) {
        std::cout << "FAIL: Should have 10 kills" << std::endl;
        return 1;
    }
    
    std::cout << "PASS: Progression test passed!" << std::endl;
    return 0;
}
