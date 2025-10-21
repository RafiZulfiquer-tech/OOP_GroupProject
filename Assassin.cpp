#include "Assassin.h"
#include "Attack.h"
#include <cmath>

// Starts as Rogue, adds invisibility
Assassin::Assassin(float x, float y)
    : Rogue(x, y), invisible(false), invisDuration(6.f), invisTimer(0.f) {
    className = "Assassin";
}

// Throws dagger; double damage if invisible
std::unique_ptr<Attack> Assassin::createAttack(float angleToMouse) {
    int dmg = calculateDamage();
    if (isInvisible()) dmg *= 2;

    float angleRad = angleToMouse * 3.14159f / 180.f;

    sf::Vector2f vel(
        std::cos(angleRad) * daggerSpeed,
        std::sin(angleRad) * daggerSpeed
    );

    return std::make_unique<DaggerAttack>(dmg, 400.f, position, vel, 6.f);
}

// Enter invisibility if allowed
void Assassin::vanish() {
    if (canVanish()) {
        invisible = true;
        invisTimer = invisDuration;
    }
}

// Update invisibility timer
void Assassin::update(float dt) {
    Rogue::update(dt);
    if (invisible) {
        invisTimer -= dt;
        if (invisTimer <= 0) {
            invisible = false;
            invisTimer = 0;
        }
    }
}

bool Assassin::isInvisible() const { return invisible; }

// Can vanish if not already invisible and level >= 10
bool Assassin::canVanish() const {
    return !invisible && level >= 10;
}