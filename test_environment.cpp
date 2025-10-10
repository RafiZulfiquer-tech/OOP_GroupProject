#include "Environment.h"
#include "Entity.h"
#include <cassert>
#include <iostream>

void test_spawn_and_remove() {
    Environment env(10, 10);
    Entity e1(1, 1, 1);
    Entity e2(2, 2, 1);
    env.spawnEntity(&e1);
    env.spawnEntity(&e2);
    assert(env.getEntityCount() == 2);
    env.removeEntity(&e1);
    assert(env.getEntityCount() == 1);
    try {
        env.removeEntity(&e1);
        assert(false); // Should throw
    } catch (const std::runtime_error&) {
        std::cout << "Caught expected error\n";
    }
}

void test_clamp_position() {
    Environment env(100, 100);
    int x = -10, y = 200;
    env.clampPosition(x, y);
    assert(x == 0 && y == 100);
}

void test_collision() {
    Entity e1(0, 0, 1);
    Entity e2(0, 1, 1);
    Environment env(10, 10);
    assert(env.checkCollision(&e1, &e2));
}

int main() {
    test_spawn_and_remove();
    test_clamp_position();
    test_collision();
    std::cout << "All tests passed!\n";
    return 0;
}
