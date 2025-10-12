#include "Assassin.h"

Assassin::Assassin(float x, float y)
    : Rogue(x, y), invisible(false), invisDuration(6.f), invisTimer(0.f) { className = "Assassin"; }

std::unique_ptr<Attack> Assassin::createAttack() {
    int dmg = calculateDamage();
    if (isInvisible()) dmg *= 2; // bonus for attacking from stealth
    return std::make_unique<Attack>(dmg, daggerSpeed);
}

void Assassin::vanish() {
    if (canVanish()) {
        invisible = true;
        invisTimer = invisDuration;
    }
}

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
bool Assassin::canVanish() const { return !invisible && level >= 10; }
