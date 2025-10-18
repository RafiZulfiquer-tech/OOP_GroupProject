#include "../../Warrior.h"
#include <iostream>

int main() {
    std::cout << "Testing XP..." << std::endl;
    
    Warrior player(100.f, 100.f);
    
    if (player.getLevel() != 1 || player.getXP() != 0) {
        std::cout << "FAIL: Wrong starting values" << std::endl;
        return 1;
    }
    
    player.addXP(50);
    if (player.getXP() != 50) {
        std::cout << "FAIL: XP not added" << std::endl;
        return 1;
    }
    
    player.addKill();
    player.addKill();
    if (player.getKills() != 2) {
        std::cout << "FAIL: Kills not tracked" << std::endl;
        return 1;
    }
    
    std::cout << "PASS: XP test passed!" << std::endl;
    return 0;
}
