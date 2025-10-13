#ifndef WIZARD_H
#define WIZARD_H

#include "Player.h"
#include <memory>

class Attack;  // Forward declaration

class Wizard : public Player {
protected:
    int mana;
    int maxMana;
    float manaRegen;
    int boltDamage;
public:
    Wizard(float x, float y);
    std::unique_ptr<Attack> createAttack(float angleToMouse) override;
    void evolve() override;
    void update(float dt) override;
    int getMana() const;
    int getMaxMana() const;
    bool hasMana(int cost) const;
    void consumeMana(int cost);

        // change colour of character
    void draw(sf::RenderWindow& window) override;
};

#endif // WIZARD_H