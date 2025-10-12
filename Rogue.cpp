#include "Rogue.h"
#include <cstdlib>

Rogue::Rogue(float x, float y)
    : Player(x, y, "Rogue"), daggerSpeed(200.f), daggerDamage(10), critChance(0.05f) {}

std::unique_ptr<Attack> Rogue::createAttack() {
    int dmg = calculateDamage();
    return std::make_unique<Attack>(dmg, daggerSpeed);
}

void Rogue::evolve() { evolved = true; }
float Rogue::getCritChance() const { return critChance; }
int Rogue::calculateDamage() const {
    // Example crit logic
    if (static_cast<float>(rand()) / RAND_MAX < critChance)
        return daggerDamage * 2;
    return daggerDamage;
}
