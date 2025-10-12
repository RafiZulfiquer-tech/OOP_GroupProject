#include "Archmage.h"

Archmage::Archmage(float x, float y)
    : Wizard(x, y), meteorCost(40), meteorRadius(50.f) { className = "Archmage"; }

std::unique_ptr<Attack> Archmage::createAttack() {
    if (canCastMeteor()) return meteorAttack();
    return Wizard::createAttack();
}

std::unique_ptr<Attack> Archmage::meteorAttack() {
    consumeMana(meteorCost);
    return std::make_unique<Attack>(boltDamage * 3, meteorRadius); // example
}

bool Archmage::canCastMeteor() const { return hasMana(meteorCost) && level >= 10; }
