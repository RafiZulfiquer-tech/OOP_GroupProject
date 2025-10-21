#!/bin/bash

echo "Creating integration test files..."

# Create directories
mkdir -p tests/integration
mkdir -p tests/build

# Create Test 1: Combat
cat > tests/integration/combat_test.cpp << 'END'
#include "../../Warrior.h"
#include "../../Goblin.h"
#include "../../Environment.h"
#include <iostream>

int main() {
    std::cout << "Testing combat..." << std::endl;
    
    Environment env(800, 600);
    Warrior* player = new Warrior(100.f, 100.f);
    Goblin* enemy = new Goblin(100.f, 100.f);
    
    env.spawnEntity(player);
    env.spawnEntity(enemy);
    
    if (!env.checkCollision(player, enemy)) {
        std::cout << "FAIL: Should collide" << std::endl;
        return 1;
    }
    
    int oldHealth = enemy->getHealth();
    enemy->takeDamage(20);
    
    if (enemy->getHealth() >= oldHealth) {
        std::cout << "FAIL: Health should decrease" << std::endl;
        return 1;
    }
    
    player->addXP(10);
    player->addKill();
    
    env.clearEntities();
    std::cout << "PASS: Combat test passed!" << std::endl;
    return 0;
}
END

# Create Test 2: XP
cat > tests/integration/xp_test.cpp << 'END'
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
END

# Create Test 3: Mana
cat > tests/integration/mana_test.cpp << 'END'
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
END

# Create Test 4: Enemy
cat > tests/integration/enemy_test.cpp << 'END'
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
END

# Create Test 5: Environment
cat > tests/integration/Environment_test.cpp << 'END'
#include "../../Environment.h"
#include "../../Enemy.h"
#include "../../Warrior.h"
#include <iostream>

int main() {
    std::cout << "Testing environment..." << std::endl;
    
    Environment env(800, 600);
    Enemy* e1 = new Enemy(100.f, 100.f, 50, 80.f, 15, 25);
    Enemy* e2 = new Enemy(200.f, 200.f, 50, 80.f, 15, 25);
    Warrior* p = new Warrior(300.f, 300.f);
    
    env.spawnEntity(e1);
    env.spawnEntity(e2);
    env.spawnEntity(p);
    
    if (env.getEntityCount() != 3) {
        std::cout << "FAIL: Wrong entity count" << std::endl;
        return 1;
    }
    
    e1->takeDamage(100);
    env.removeDeadEntities();
    
    if (env.getEntityCount() != 2) {
        std::cout << "FAIL: Dead entity not removed" << std::endl;
        return 1;
    }
    
    env.clearEntities();
    std::cout << "PASS: Environment test passed!" << std::endl;
    return 0;
}
END

echo "✓ Created 5 test files"
echo ""
echo "Building and running tests..."
echo "================================"

# Build and run each test
tests=(combat_test xp_test mana_test enemy_test environment_test)

for test in "${tests[@]}"; do
    echo ""
    echo "--- $test ---"
    
    g++ -std=c++17 -Wno-unused-parameter -I. \
        tests/integration/${test}.cpp \
        Entity.cpp Environment.cpp Player.cpp Warrior.cpp Wizard.cpp Rogue.cpp \
        Knight.cpp Assassin.cpp Archmage.cpp Enemy.cpp Goblin.cpp GoblinBrute.cpp \
        GoblinLord.cpp Controller.cpp \
        -lsfml-graphics -lsfml-window -lsfml-system \
        -o tests/build/${test} 2>/dev/null
    
    if [ -f tests/build/${test} ]; then
        ./tests/build/${test}
    else
        echo "BUILD FAILED"
    fi
done

echo ""
echo "================================"
echo "All done!"
