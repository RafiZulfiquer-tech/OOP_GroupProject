#include "Wizard.h"

Wizard::Wizard(float x, float y)
    : Player(x, y, "Wizard"), mana(100), maxMana(100), manaRegen(10.f), boltDamage(20) {}

std::unique_ptr<Attack> Wizard::createAttack() {
    if (hasMana(10)) {
        consumeMana(10);
        return std::make_unique<Attack>(boltDamage, 60.0f);
    }
    return nullptr;
}

void Wizard::evolve() { evolved = true; }
void Wizard::update(float dt) {
    currentCooldown = std::max(0.f, currentCooldown - dt);
    mana = std::min(maxMana, mana + static_cast<int>(manaRegen * dt));
}

int Wizard::getMana() const { return mana; }
int Wizard::getMaxMana() const { return maxMana; }
bool Wizard::hasMana(int cost) const { return mana >= cost; }
void Wizard::consumeMana(int cost) { mana = std::max(0, mana - cost); }
