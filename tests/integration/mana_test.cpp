#include "../../Wizard.h"
#include <iostream>

int main() {
    std::cout << "Testing mana..." << std::endl;
    
    Wizard wizard(100.f, 100.f);
    
    if (wizard.getMana() != 100) {
        std::cout << "FAIL: Wrong starting mana" << std::endl;
        return 1;
    }
    
    wizard.consumeMana(30);
    if (wizard.getMana() != 70) {
        std::cout << "FAIL: Mana not consumed" << std::endl;
        return 1;
    }
    
    wizard.update(2.f);
    if (wizard.getMana() <= 70) {
        std::cout << "FAIL: Mana not regenerated" << std::endl;
        return 1;
    }
    
    std::cout << "PASS: Mana test passed!" << std::endl;
    return 0;
}
