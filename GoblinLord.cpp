#include "GoblinLord.h"
#include "Goblin.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>

GoblinLord::GoblinLord(float x, float y, float hp, float speed, float damage)
    : Enemy(x, y, hp, speed, damage, 100),  // 100 XP reward
      armor(20), summonCooldown(10), summonTimer(0.f),
      maxSummons(5), currentSummons(0) {
    radius = 25.f;
}

GoblinLord::~GoblinLord() {
    // Clean up summoned goblins
    for (auto goblin : summonedGoblins) {
        delete goblin;
    }
    summonedGoblins.clear();
}

void GoblinLord::takeDamage(int dmg) {
    // Reduce damage by armor, never below 1
    int reducedDamage = std::max(1, dmg - armor);
    Entity::takeDamage(reducedDamage);

    // 20% chance to lose 1 armor when hit
    if (rand() % 5 == 0) armor = std::max(0, armor - 1);
}

void GoblinLord::update(float dt) {
    Enemy::update(dt);
    // Countdown summon cooldown
    summonTimer = std::max(0.f, summonTimer - dt);
}

bool GoblinLord::canSummon() const {
    return summonTimer <= 0 && currentSummons < maxSummons;
}

std::vector<Goblin*> GoblinLord::summonGoblins(int count) {
    std::vector<Goblin*> newGoblins;
    int actualCount = std::min(count, maxSummons - currentSummons);

    for (int i = 0; i < actualCount; ++i) {
        // Position goblins around the Lord in a circle
        float angle = (2.f * 3.14159f * i) / actualCount;
        float spawnX = position.x + std::cos(angle) * (radius + 30.f);
        float spawnY = position.y + std::sin(angle) * (radius + 30.f);

        Goblin* goblin = new Goblin(spawnX, spawnY);
        newGoblins.push_back(goblin);
        summonedGoblins.push_back(goblin);
        currentSummons++;
    }

    summonTimer = summonCooldown;
    return newGoblins;
}

void GoblinLord::notifyGoblinDeath() {
    if (currentSummons > 0) currentSummons--;
}

void GoblinLord::draw(sf::RenderWindow& window) {
    // Draw body
    sf::CircleShape shape(radius);
    shape.setPosition(position.x - radius, position.y - radius);
    shape.setFillColor(sf::Color(100, 0, 100)); // Purple

    shape.setOutlineThickness(6.f);
    shape.setOutlineColor(sf::Color(255, 215, 0)); // Gold outline
    window.draw(shape);

    // Draw crown
    sf::ConvexShape crown;
    crown.setPointCount(3);
    crown.setPoint(0, sf::Vector2f(position.x, position.y - radius - 8));
    crown.setPoint(1, sf::Vector2f(position.x - 10, position.y - radius + 5));
    crown.setPoint(2, sf::Vector2f(position.x + 10, position.y - radius + 5));
    crown.setFillColor(sf::Color(255, 215, 0));
    window.draw(crown);
}

void GoblinLord::onDeath() {
    // Kill all summoned goblins when Lord dies
    for (auto goblin : summonedGoblins) {
        if (goblin && goblin->isAlive()) {
            goblin->takeDamage(goblin->getHealth());
        }
    }
}