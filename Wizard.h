#ifndef WIZARD_H
#define WIZARD_H

#include "Player.h"

class Wizard : public Player {
private:
    int mana;
    int maxMana;
    float manaRegen;
    int boltDamage;
public:
    Wizard(float x, float y);
    std::unique_ptr<Attack> createAttack() override;
    void evolve() override;
    void update(float dt) override;
    int getMana() const;
    int getMaxMana() const;
    bool hasMana(int cost) const;
    void consumeMana(int cost);
};

#endif // WIZARD_H
