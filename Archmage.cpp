#include "Archmage.h"
#include "Attack.h"
#include <cmath>

Archmage::Archmage(float x, float y)
    : Wizard(x, y), meteorCost(40), meteorRadius(50.f) { className = "Archmage"; }

std::unique_ptr<Attack> Archmage::createAttack(float angleToMouse) {
    if (canCastMeteor()) return meteorAttack(angleToMouse);
    return Wizard::createAttack(angleToMouse);
}

std::unique_ptr<Attack> Archmage::meteorAttack(float angleToMouse) {
    consumeMana(meteorCost);
    
    float angleRad = angleToMouse * 3.14159f / 180.f;
    float meteorSpeed = 200.f;
    
    sf::Vector2f vel(
        std::cos(angleRad) * meteorSpeed,
        std::sin(angleRad) * meteorSpeed
    );
    
    return std::make_unique<ProjectileAttack>(boltDamage * 3, 500.f, position, vel, meteorRadius);
}

bool Archmage::canCastMeteor() const { return hasMana(meteorCost) && level >= 10; }

