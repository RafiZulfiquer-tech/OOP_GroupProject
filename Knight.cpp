#include "Knight.h"
#include "Attack.h"

Knight::Knight(float x, float y)
    : Warrior(x, y), chargeSpeed(180.f), canCharge(true) {
    className = "Knight";
}

std::unique_ptr<Attack> Knight::createAttack(float angleToMouse) {
    if (canUseCharge())
        return chargeAttack(angleToMouse);
    return Warrior::createAttack(angleToMouse);
}

std::unique_ptr<Attack> Knight::chargeAttack(float angleToMouse) {
    int damage = static_cast<int>(getMeleeDamage() * 2);
    float range = getMeleeRange() + 20;
    
    return std::make_unique<SlashAttack>(damage, range, position, angleToMouse);
}

bool Knight::canUseCharge() const {
    return canCharge && level >= 10;
}