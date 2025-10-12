#ifndef ROGUE_H
#define ROGUE_H

#include "Player.h"

class Rogue : public Player {
private:
    float daggerSpeed;
    int daggerDamage;
    float critChance;
public:
    Rogue(float x, float y);
    std::unique_ptr<Attack> createAttack() override;
    void evolve() override;
    float getCritChance() const;
    int calculateDamage() const;
};

#endif // ROGUE_H
