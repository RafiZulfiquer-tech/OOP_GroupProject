#ifndef GOBLINLORD_H
#define GOBLINLORD_H

#include "Enemy.h"
#include <vector>

class Goblin;

class GoblinLord : public Enemy {
private:
    int armor;
    float summonCooldown;
    float summonTimer;
    int maxSummons;
    int currentSummons;
    std::vector<Goblin*> summonedGoblins;
public:
    GoblinLord(float x, float y, float hp = 300, float speed = 50.f, float damage = 30);
    ~GoblinLord();
    void takeDamage(int dmg) override;
    void update(float dt) override;
    bool canSummon() const;
    std::vector<Goblin*> summonGoblins(int count);
    void notifyGoblinDeath();
    void draw(sf::RenderWindow& window) override;
    void onDeath();
};

#endif // GOBLINLORD_H
