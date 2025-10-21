#ifndef ARCHMAGE_H
#define ARCHMAGE_H

#include "Wizard.h"

// Enhanced Wizard with meteor ability
class Archmage : public Wizard {
private:
    int meteorCost;       // Mana cost for meteor
    float meteorRadius;   // Explosion radius
public:
    Archmage(float x, float y);
    std::unique_ptr<Attack> createAttack(float angleToMouse) override;
    std::unique_ptr<Attack> meteorAttack(float angleToMouse);
    bool canCastMeteor() const;
};

#endif // ARCHMAGE_H