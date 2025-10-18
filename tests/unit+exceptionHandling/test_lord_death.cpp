#include "GoblinLord.h"
#include "Goblin.h"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Testing GoblinLord on death (kills all summons)..." << std::endl;
    try {
        GoblinLord lord(400.f, 300.f); // HP = 300, armor = 20

        std::vector<Goblin*> goblins = lord.summonGoblins(3);

        // Verify all goblins are alive
        for (auto goblin : goblins) {
            assert(goblin->isAlive() == true);
        }

        // Kill the lord with enough damage (at least HP + armor)
        lord.takeDamage(320); // 320-20=300, Lord's HP becomes 0
        assert(lord.isAlive() == false);

        lord.onDeath();

        // All summoned goblins should be dead
        for (auto goblin : goblins) {
            assert(goblin->isAlive() == false);
        }

        // No manual delete; destructor handles it

        std::cout << "✓ PASSED: GoblinLord on death" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ FAILED: " << e.what() << std::endl;
        return 1;
    }
}
