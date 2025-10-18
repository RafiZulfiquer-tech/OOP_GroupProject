#include "environment.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

int main() {
    std::cout << "Testing spawn null entity (should throw)..." << std::endl;
    try {
        Environment env(800, 600);
        bool exceptionThrown = false;
        
        try {
            env.spawnEntity(nullptr);
        } catch (const std::invalid_argument& e) {
            exceptionThrown = true;
            std::cout << "  Correctly caught exception: " << e.what() << std::endl;
        }
        
        assert(exceptionThrown);
        std::cout << "✓ PASSED: Spawn null entity exception handling" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ FAILED: " << e.what() << std::endl;
        return 1;
    }
}