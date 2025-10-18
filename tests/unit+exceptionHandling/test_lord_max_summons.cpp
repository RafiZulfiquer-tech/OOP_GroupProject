#include "GoblinLord.h"
#include "Goblin.h"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Testing GoblinLord max summons limit..." << std::endl;
    try {
        GoblinLord lord(400.f, 300.f);

        // Try to summon 10 goblins but max is 5
        std::vector<Goblin*> goblins = lord.summonGoblins(10);

        assert(goblins.size() == 5); // Should only create 5

        // Can't summon more
        assert(lord.canSummon() == false);

        // No manual delete; destructor handles it

        std::cout << "✓ PASSED: GoblinLord max summons limit" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ FAILED: " << e.what() << std::endl;
        return 1;
    }
}
