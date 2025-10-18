#!/bin/bash

# Test runner script for individual test files

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

BUILD_DIR="tests/build"
PASSED=0
FAILED=0
TOTAL=0

# List of all test executables
TESTS=(
    "test_entity_creation"
    "test_entity_damage"
    "test_brute_armor"
    "test_brute_negative_damage"
    "test_lord_summon"
    "test_lord_max_summons"
    "test_lord_death"
    "test_env_collision"
    "test_env_spawn_null"
    "test_env_remove_dead"
    "test_player_movement"
    "test_player_xp"
    "test_wizard_mana"
    "test_rogue_crit"
    "test_enemy_movement"
    "test_enemy_attack_cooldown"
    "test_integration_combat"
)

# Print header
echo "=========================================="
echo "  Game Engine Test Suite Runner"
echo "=========================================="
echo ""

# Check if build directory exists
if [ ! -d "$BUILD_DIR" ]; then
    echo -e "${YELLOW}Build directory not found. Building tests...${NC}"
    make -f Makefile.tests all
    if [ $? -ne 0 ]; then
        echo -e "${RED}Build failed!${NC}"
        exit 1
    fi
    echo ""
fi

# Run each test
for test in "${TESTS[@]}"; do
    TOTAL=$((TOTAL + 1))
    echo "--- Running $test ---"
    
    if [ -f "$BUILD_DIR/$test" ]; then
        ./$BUILD_DIR/$test
        
        if [ $? -eq 0 ]; then
            PASSED=$((PASSED + 1))
            echo -e "${GREEN}✓ $test PASSED${NC}"
        else
            FAILED=$((FAILED + 1))
            echo -e "${RED}✗ $test FAILED${NC}"
        fi
    else
        echo -e "${RED}✗ $test executable not found${NC}"
        FAILED=$((FAILED + 1))
    fi
    
    echo ""
done

# Print summary
echo "=========================================="
echo "  Test Summary"
echo "=========================================="
echo -e "Total:  $TOTAL"
echo -e "${GREEN}Passed: $PASSED${NC}"
echo -e "${RED}Failed: $FAILED${NC}"
echo "=========================================="

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}🎉 All tests passed! 🎉${NC}"
    exit 0
else
    echo -e "${RED}⚠️  Some tests failed ⚠️${NC}"
    exit 1
fi
