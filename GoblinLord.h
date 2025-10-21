#ifndef GOBLINLORD_H
#define GOBLINLORD_H

#include "Enemy.h"
#include <vector>

// Forward declaration to avoid circular dependency
class Goblin;

// Special enemy that can summon goblins and has armor
class GoblinLord : public Enemy {
private:
    int armor;                        // Reduces incoming damage
    float summonCooldown;            // Time between summon attempts
    float summonTimer;              // Countdown until next possible summon
    int maxSummons;                 // Max goblins that can be summoned at once
    int currentSummons;             // Current active summons
    std::vector<Goblin*> summonedGoblins; // Track all summoned goblins

public:
    // Constructor with default stats
    GoblinLord(float x, float y, float hp = 300, float speed = 50.f, float damage = 30);
    
    // Destructor cleans up summoned goblins
    ~GoblinLord();

    // Overrides damage behavior to account for armor
    void takeDamage(int dmg) override;

    // Updates summon timer and base enemy logic
    void update(float dt) override;

    // Check if the lord can currently summon
    bool canSummon() const;

    // Summon up to N goblins and return them
    std::vector<Goblin*> summonGoblins(int count);

    // Notify lord that a summoned goblin has died
    void notifyGoblinDeath();

    // Render the lord on screen
    void draw(sf::RenderWindow& window) override;

    // Called when the lord dies — kills remaining goblins
    void onDeath();
};

#endif // GOBLINLORD_H