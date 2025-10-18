#include "Player.h"
#include "Warrior.h"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Testing Player XP and kills..." << std::endl;
    try {
        Warrior player(0.f, 0.f);
        
        assert(player.getXP() == 0);
        assert(player.getKills() == 0);
        
        player.addXP(50);
        assert(player.getXP() == 50);
        
        player.addKill();
        assert(player.getKills() == 1);
        
        player.addKill();
        player.addXP(100);
        assert(player.getKills() == 2);
        assert(player.getXP() == 150);
        
        std::cout << "✓ PASSED: Player XP and kills" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ FAILED: " << e.what() << std::endl;
        return 1;
    }
}