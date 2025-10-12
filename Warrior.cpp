#include "Warrior.h"

Warrior::Warrior(float x, float y)
    : Player(x, y, "Warrior"), meleeDamage(15.f), meleeRange(40.f) {}

std::unique_ptr<Attack> Warrior::createAttack() {
    // Example: return a melee attack specific to Warrior
    return std::make_unique<Attack>(meleeDamage, meleeRange);
}

void Warrior::evolve() { evolved = true; }
float Warrior::getMeleeDamage() const { return meleeDamage; }
float Warrior::getMeleeRange() const { return meleeRange; }
