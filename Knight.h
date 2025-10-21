#ifndef KNIGHT_H
#define KNIGHT_H

#include "Warrior.h"

// Knight class inherits from Warrior and adds special charge attack capabilities
class Knight : public Warrior {
private:
    float chargeSpeed;  // Speed while charging
    bool canCharge;     // Flag indicating if charge attack is available
public:
    Knight(float x, float y);

    // Overrides Warrior's createAttack to use charge attack if available
    std::unique_ptr<Attack> createAttack(float angleToMouse) override;

    // Performs a powerful charge attack at the given angle
    std::unique_ptr<Attack> chargeAttack(float angleToMouse);

    // Checks if the Knight can use the charge attack (level requirement + availability)
    bool canUseCharge() const;
};

#endif // KNIGHT_H