#include "GoblinBrute.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

int main() {
    std::cout << "Testing GoblinBrute negative damage exception..." << std::endl;
    try {
        // Try with just x, y (common pattern like Goblin)
        GoblinBrute brute(0.f, 0.f);
        
        bool exceptionThrown = false;
        try {
            brute.takeDamage(-10);
        } catch (const std::invalid_argument& e) {
            exceptionThrown = true;
            std::cout << "  Correctly caught exception: " << e.what() << std::endl;
        }
        
        assert(exceptionThrown);
        std::cout << "✓ PASSED: GoblinBrute negative damage exception" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ FAILED: " << e.what() << std::endl;
        return 1;
    }
}