#include "../../Goblin.h"
#include "../../GoblinBrute.h"
#include <iostream>

int main() {
    std::cout << "Testing enemies..." << std::endl;
    
    Goblin goblin(100.f, 100.f);
    GoblinBrute brute(200.f, 200.f);
    
    if (brute.getHealth() <= goblin.getHealth()) {
        std::cout << "FAIL: Brute should have more health" << std::endl;
        return 1;
    }
    
    int bruteHP = brute.getHealth();
    brute.takeDamage(20);
    if (bruteHP - brute.getHealth() >= 20) {
        std::cout << "FAIL: Armor should reduce damage" << std::endl;
        return 1;
    }
    
    std::cout << "PASS: Enemy test passed!" << std::endl;
    return 0;
}
