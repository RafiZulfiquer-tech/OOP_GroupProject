#ifndef WIZARD_H
#define WIZARD_H

#include "Player.h"
#include <memory>

// Forward declaration to avoid circular dependency
class Attack;

class Wizard : public Player {
protected:
    int mana;          // Current mana points for casting spells
    int maxMana;       // Maximum mana capacity
    float manaRegen;   // Mana regeneration rate (per second)
    int boltDamage;    // Damage dealt by magic bolt attack

public:
    // Constructor initializes position and wizard-specific attributes
    Wizard(float x, float y);

    // Create a ranged magic attack (overrides base Player method)
    std::unique_ptr<Attack> createAttack(float angleToMouse) override;

    // Evolution behavior when leveling up or triggered (overrides base Player method)
    void evolve() override;

    // Update wizard status each frame, e.g., mana regeneration (overrides base Player method)
    void update(float dt) override;

    // Get current mana
    int getMana() const;

    // Get maximum mana
    int getMaxMana() const;

    // Check if wizard has enough mana to perform an action
    bool hasMana(int cost) const;

    // Deduct mana cost when casting spells or abilities
    void consumeMana(int cost);

    // Draw wizard character with custom color (overrides base Player method)
    void draw(sf::RenderWindow& window) override;
};

#endif // WIZARD_H