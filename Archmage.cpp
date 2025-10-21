#include "Archmage.h"
#include "Attack.h"
#include <cmath>

// Inherits from Wizard, adds meteor attack
Archmage::Archmage(float x, float y)
    : Wizard(x, y), meteorCost(40), meteorRadius(50.f) {
    className = "Archmage";
}

// Use meteor if available, else default attack
std::unique_ptr<Attack> Archmage::createAttack(float angleToMouse) {
    if (canCastMeteor()) return meteorAttack(angleToMouse);
    return Wizard::createAttack(angleToMouse);
}

// Create meteor projectile
std::unique_ptr<Attack> Archmage::meteorAttack(float angleToMouse) {
    consumeMana(meteorCost);
    
    float angleRad = angleToMouse * 3.14159f / 180.f;
    float speed = 200.f;

    // Direction vector
    sf::Vector2f vel(
        std::cos(angleRad) * speed,
        std::sin(angleRad) * speed
    );

    return std::make_unique<ProjectileAttack>(
        boltDamage * 3, 500.f, position, vel, meteorRadius
    );
}

// Meteor requires mana and level 10
bool Archmage::canCastMeteor() const {
    return hasMana(meteorCost) && level >= 10;
}