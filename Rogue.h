#ifndef ROGUE_H
#define ROGUE_H

#include "Player.h"

class Rogue : public Player {
protected:
    float daggerSpeed;
    int daggerDamage;
    float critChance;
public:
    Rogue(float x, float y);
    std::unique_ptr<Attack> createAttack(float angleToMouse) override;
    void evolve() override;
    float getCritChance() const;
    int calculateDamage() const;
        // change colour of character
    void draw(sf::RenderWindow& window) override;
};

#endif // ROGUE_H