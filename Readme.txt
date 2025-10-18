Game Engine Testing Suite
Comprehensive unit and integration testing framework for the game engine.
Test Organization
Unit Tests
Each component has its own test file that tests individual functionality in isolation:

test_entity.cpp - Tests the base Entity class

Entity creation and initialization
Health management and damage
Death conditions
Edge cases (overkill, zero damage, negative health)


test_environment.cpp - Tests the Environment system

Entity spawning and removal
Collision detection
Position clamping
Dead entity cleanup
Exception handling for invalid operations


test_enemy.cpp - Tests Enemy and Goblin classes

Enemy creation and movement
Attack cooldown system
Movement toward targets
Death conditions


test_goblin_brute.cpp - Tests GoblinBrute armor mechanics

Armor reduction on damage
Minimum damage (always at least 1)
Armor depletion
Exception handling for negative damage


test_goblin_lord.cpp - Tests GoblinLord summoning

Goblin summoning mechanics
Maximum summon limits
Summon cooldown system
Death notification system
onDeath() behavior (kills all summons)


test_player.cpp - Tests Player classes (Warrior, Wizard, Rogue)

Player creation and stats
Movement system
Attack cooldown
XP and leveling
Class-specific mechanics (mana, crits, melee)


test_controller.cpp - Tests input handling

Attack input detection
Event handling
Mouse angle calculation
Input reset behavior



Integration Tests
test_integration.cpp - Tests how components work together:

Player-Enemy collision
Combat scenarios
Multiple enemies in environment
GoblinLord summoning integration
Armor system in combat
Player leveling system
Wizard mana in combat
Rogue critical hits
Enemy swarm behavior
Player death scenarios
Exception handling across systems
Memory management