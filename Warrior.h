#ifndef WARRIOR_H
#define WARRIOR_H

#include "Player.h"

class Warrior : public Player {
private:
    float meleeDamage;
    float meleeRange;
public:
    Warrior(float x, float y);
    std::unique_ptr<Attack> createAttack() override;
    void evolve() override;
    float getMeleeDamage() const;
    float getMeleeRange() const;
};

#endif // WARRIOR_H
