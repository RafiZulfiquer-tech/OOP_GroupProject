#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Entity.h"

// Forward declaration for Attack class (used in createAttack)
class Attack;

// Player class inherits from Entity, representing the player character
class Player : public Entity {
protected:
    float speed;             // Movement speed of the player
    int xp;                  // Experience points accumulated by the player
    int level;               // Current player level
    int kills;               // Number of kills the player has made
    float attackCooldown;    // Time (seconds) required between attacks
    float currentCooldown;   // Current cooldown timer for the next attack
    std::string className;   // Player's class type (e.g., Warrior, Wizard)
    bool evolved;            // Whether the player has evolved (class upgrade)

public:
    // Constructor: initializes position and class type, with default class "Warrior"
    Player(float x, float y, const std::string& cls = "Warrior");

    // Virtual destructor (defaulted)
    virtual ~Player() = default;

    // Move the player based on input direction and elapsed time
    virtual void move(sf::Vector2f direction, float dt);

    // Returns true if player can attack (attack cooldown expired)
    virtual bool canAttack() const;

    // Create an attack object, depending on player class (to be overridden in subclasses)
    virtual std::unique_ptr<Attack> createAttack(float angleToMouse);

    // Resets the attack cooldown after an attack is performed
    void resetCooldown();

    // Add experience points and handle level-ups
    void addXP(int amount);

    // Increment the kill count by one
    void addKill();

    // Evolve the player class (can be overridden for specific behaviors)
    virtual void evolve();

    // Getters for player stats and info
    int getLevel() const;
    int getXP() const;
    int getKills() const;
    std::string getClassName() const;
    float getSpeed() const;
    bool isEvolved() const;
    float getCooldown() const;

    // Calculate XP required for next level (e.g., level * 100)
    int getXPNeeded() const;

    // Update the player state (e.g., cooldowns), overrides Entity method
    void update(float dt) override;

    // Draw the player on the window, overrides Entity method
    void draw(sf::RenderWindow& window) override;
};

#endif // PLAYER_H