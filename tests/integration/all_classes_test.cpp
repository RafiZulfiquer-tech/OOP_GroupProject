#include "../../Warrior.h"
#include "../../Wizard.h"
#include "../../Rogue.h"
#include <iostream>

int main() {
    std::cout << "Testing all player classes..." << std::endl;
    
    Warrior warrior(100.f, 100.f);
    Wizard wizard(200.f, 200.f);
    Rogue rogue(300.f, 300.f);
    
    // Check class names
    if (warrior.getClassName() != "Warrior") {
        std::cout << "FAIL: Wrong warrior class name" << std::endl;
        return 1;
    }
    
    if (wizard.getClassName() != "Wizard") {
        std::cout << "FAIL: Wrong wizard class name" << std::endl;
        return 1;
    }
    
    if (rogue.getClassName() != "Rogue") {
        std::cout << "FAIL: Wrong rogue class name" << std::endl;
        return 1;
    }
    
    // All start at same level
    if (warrior.getLevel() != wizard.getLevel() || wizard.getLevel() != rogue.getLevel()) {
        std::cout << "FAIL: All should start at same level" << std::endl;
        return 1;
    }
    
    // Test unique abilities
    // Wizard has mana
    if (wizard.getMana() <= 0) {
        std::cout << "FAIL: Wizard should have mana" << std::endl;
        return 1;
    }
    
    // Rogue has crit chance
    if (rogue.getCritChance() <= 0) {
        std::cout << "FAIL: Rogue should have crit chance" << std::endl;
        return 1;
    }
    
    // Warrior has melee damage
    if (warrior.getMeleeDamage() <= 0) {
        std::cout << "FAIL: Warrior should have melee damage" << std::endl;
        return 1;
    }
    
    std::cout << "PASS: All classes test passed!" << std::endl;
    return 0;
}
