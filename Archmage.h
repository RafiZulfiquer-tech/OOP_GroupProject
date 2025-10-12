#ifndef ARCHMAGE_H
#define ARCHMAGE_H

#include "Wizard.h"

class Archmage : public Wizard {
private:
    int meteorCost;
    float meteorRadius;
public:
    Archmage(float x, float y);
    std::unique_ptr<Attack> createAttack() override;
    std::unique_ptr<Attack> meteorAttack();
    bool canCastMeteor() const;
};

#endif // ARCHMAGE_H
