#include "GoblinLord.h"
#include "Goblin.h"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Testing GoblinLord summon goblins..." << std::endl;
    try {
        GoblinLord lord(400.f, 300.f);
        
        assert(lord.canSummon() == true);
        
        std::vector<Goblin*> goblins = lord.summonGoblins(3);
        
        assert(goblins.size() == 3);
        assert(lord.canSummon() == false); // Cooldown should be active
        
        // DON'T delete goblins - GoblinLord destructor handles it!
        
        std::cout << "✓ PASSED: GoblinLord summon goblins" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ FAILED: " << e.what() << std::endl;
        return 1;
    }
}