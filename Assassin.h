#ifndef ASSASSIN_H
#define ASSASSIN_H

#include "Rogue.h"

// Rogue subclass with invisibility and bonus damage
class Assassin : public Rogue {
private:
    bool invisible;        // Invisibility state
    float invisDuration;   // Max time invisible
    float invisTimer;      // Time left invisible
public:
    Assassin(float x, float y);
    std::unique_ptr<Attack> createAttack(float angleToMouse) override;
    void vanish();                  // Activate invisibility
    void update(float dt) override;
    bool isInvisible() const;
    bool canVanish() const;        // Conditions for vanishing
};

#endif // ASSASSIN_H