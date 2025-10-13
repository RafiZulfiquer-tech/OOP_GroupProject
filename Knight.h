#ifndef KNIGHT_H
#define KNIGHT_H

#include "Warrior.h"

class Knight : public Warrior {
private:
    float chargeSpeed;
    bool canCharge;
public:
    Knight(float x, float y);
    std::unique_ptr<Attack> createAttack(float angleToMouse) override;
    std::unique_ptr<Attack> chargeAttack(float angleToMouse);
    bool canUseCharge() const;
};

#endif // KNIGHT_H
