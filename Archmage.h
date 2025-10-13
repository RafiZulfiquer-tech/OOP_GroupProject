#ifndef ARCHMAGE_H
#define ARCHMAGE_H

#include "Wizard.h"

class Archmage : public Wizard {
private:
    int meteorCost;
    float meteorRadius;
public:
    Archmage(float x, float y);
    std::unique_ptr<Attack> createAttack(float angleToMouse) override;
    std::unique_ptr<Attack> meteorAttack(float angleToMouse);
    bool canCastMeteor() const;
};

#endif // ARCHMAGE_H