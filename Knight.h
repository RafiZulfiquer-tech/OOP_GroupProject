#ifndef KNIGHT_H
#define KNIGHT_H

#include "Warrior.h"

class Knight : public Warrior {
private:
    float chargeSpeed;
    bool canCharge;
public:
    Knight(float x, float y);
    std::unique_ptr<Attack> createAttack() override;
    std::unique_ptr<Attack> chargeAttack();
    bool canUseCharge() const;
};

#endif // KNIGHT_H
