#include "Knight.h"

Knight::Knight(float x, float y)
    : Warrior(x, y), chargeSpeed(180.f), canCharge(true) { className = "Knight"; }

std::unique_ptr<Attack> Knight::createAttack() {
    if (canUseCharge()) return chargeAttack();
    return Warrior::createAttack();
}

std::unique_ptr<Attack> Knight::chargeAttack() {
    return std::make_unique<Attack>(getMeleeDamage() * 2, getMeleeRange() + 20);
}

bool Knight::canUseCharge() const { return canCharge && level >= 10; }
