#ifndef ASSASSIN_H
#define ASSASSIN_H

#include "Rogue.h"

class Assassin : public Rogue {
private:
    bool invisible;
    float invisDuration;
    float invisTimer;
public:
    Assassin(float x, float y);
    std::unique_ptr<Attack> createAttack() override;
    void vanish();
    void update(float dt) override;
    bool isInvisible() const;
    bool canVanish() const;
};

#endif // ASSASSIN_H
