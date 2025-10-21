#!/bin/bash

echo "Setting up integration tests..."

# Create directories
mkdir -p tests/integration
mkdir -p tests/build

echo "Building and running tests..."
echo ""

# Test 1: Combat
echo "=== Combat Test ==="
g++ -std=c++17 -Wno-unused-parameter -I. \
    tests/integration/combat_test.cpp \
    Entity.cpp Environment.cpp Player.cpp Warrior.cpp Wizard.cpp Rogue.cpp \
    Knight.cpp Assassin.cpp Archmage.cpp Enemy.cpp Goblin.cpp GoblinBrute.cpp \
    GoblinLord.cpp Controller.cpp \
    -lsfml-graphics -lsfml-window -lsfml-system \
    -o tests/build/combat_test 2>/dev/null

if [ -f tests/build/combat_test ]; then
    ./tests/build/combat_test
else
    echo "Build failed"
fi
echo ""

# Test 2: XP
echo "=== XP Test ==="
g++ -std=c++17 -Wno-unused-parameter -I. \
    tests/integration/xp_test.cpp \
    Entity.cpp Environment.cpp Player.cpp Warrior.cpp Wizard.cpp Rogue.cpp \
    Knight.cpp Assassin.cpp Archmage.cpp Enemy.cpp Goblin.cpp GoblinBrute.cpp \
    GoblinLord.cpp Controller.cpp \
    -lsfml-graphics -lsfml-window -lsfml-system \
    -o tests/build/xp_test 2>/dev/null

if [ -f tests/build/xp_test ]; then
    ./tests/build/xp_test
else
    echo "Build failed"
fi
echo ""

# Test 3: Mana
echo "=== Mana Test ==="
g++ -std=c++17 -Wno-unused-parameter -I. \
    tests/integration/mana_test.cpp \
    Entity.cpp Environment.cpp Player.cpp Warrior.cpp Wizard.cpp Rogue.cpp \
    Knight.cpp Assassin.cpp Archmage.cpp Enemy.cpp Goblin.cpp GoblinBrute.cpp \
    GoblinLord.cpp Controller.cpp \
    -lsfml-graphics -lsfml-window -lsfml-system \
    -o tests/build/mana_test 2>/dev/null

if [ -f tests/build/mana_test ]; then
    ./tests/build/mana_test
else
    echo "Build failed"
fi
echo ""

# Test 4: Enemy
echo "=== Enemy Test ==="
g++ -std=c++17 -Wno-unused-parameter -I. \
    tests/integration/enemy_test.cpp \
    Entity.cpp Environment.cpp Player.cpp Warrior.cpp Wizard.cpp Rogue.cpp \
    Knight.cpp Assassin.cpp Archmage.cpp Enemy.cpp Goblin.cpp GoblinBrute.cpp \
    GoblinLord.cpp Controller.cpp \
    -lsfml-graphics -lsfml-window -lsfml-system \
    -o tests/build/enemy_test 2>/dev/null

if [ -f tests/build/enemy_test ]; then
    ./tests/build/enemy_test
else
    echo "Build failed"
fi
echo ""

# Test 5: Environment
echo "=== Environment Test ==="
g++ -std=c++17 -Wno-unused-parameter -I. \
    tests/integration/environment_test.cpp \
    Entity.cpp Environment.cpp Player.cpp Warrior.cpp Wizard.cpp Rogue.cpp \
    Knight.cpp Assassin.cpp Archmage.cpp Enemy.cpp Goblin.cpp GoblinBrute.cpp \
    GoblinLord.cpp Controller.cpp \
    -lsfml-graphics -lsfml-window -lsfml-system \
    -o tests/build/environment_test 2>/dev/null

if [ -f tests/build/environment_test ]; then
    ./tests/build/environment_test
else
    echo "Build failed"
fi

echo ""
echo "=== All Tests Complete ==="
