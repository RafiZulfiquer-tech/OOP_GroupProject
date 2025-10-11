#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Entity.h"

class Player : public Entity {
 private:
  float speed;
  int xp;
  int level;
  int kills;
  float attackCooldown;
  float currentCooldown;
  std::string className;

 public:
  Player(float x, float y);

  void move(sf::Vector2f direction, float dt);
  bool canAttack() const;
  void attack();
  void addXP(int amount);
  void addKill();

  int getLevel() const;
  int getXP() const;
  int getKills() const;
  std::string getClassName() const;

  void update(float dt) override;
  void draw(sf::RenderWindow& window) override;
};

#endif

