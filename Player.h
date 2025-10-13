#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Attack;

class Player : public Entity {
protected:
    float speed;
    int xp;
    int level;
    int kills;
    float attackCooldown;
    float currentCooldown;
    std::string className;
    bool evolved;
public:
    Player(float x, float y, const std::string& cls = "Warrior");
    virtual ~Player() = default;

    virtual void move(sf::Vector2f direction, float dt);
    virtual bool canAttack() const;
    virtual std::unique_ptr<Attack> createAttack(float angleToMouse);
    void resetCooldown();
    void addXP(int amount);
    void addKill();
    virtual void evolve();

    int getLevel() const;
    int getXP() const;
    int getKills() const;
    std::string getClassName() const;
    float getSpeed() const;
    bool isEvolved() const;
    float getCooldown() const;
    int getXPNeeded() const;

    // void functions to change with different characters classes
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};

#endif // PLAYER_