#include "Player.h"
#include "Attack.h"

Player::Player(float x, float y, const std::string& cls)
    : Entity(x, y, 15.f, 100), speed(100.f), xp(0), level(1), kills(0),
      attackCooldown(1.f), currentCooldown(0.f), className(cls), evolved(false) {}

void Player::move(sf::Vector2f direction, float dt) {
    position += direction * speed * dt;
}

bool Player::canAttack() const {
    return currentCooldown <= 0.f;
}

std::unique_ptr<Attack> Player::createAttack() {
    return nullptr;
}

void Player::resetCooldown() { currentCooldown = attackCooldown; }
void Player::addXP(int amount) { xp += amount; }
void Player::addKill() { kills += 1; }
void Player::evolve() { evolved = true; }
int Player::getLevel() const { return level; }
int Player::getXP() const { return xp; }
int Player::getKills() const { return kills; }
std::string Player::getClassName() const { return className; }
float Player::getSpeed() const { return speed; }
bool Player::isEvolved() const { return evolved; }
float Player::getCooldown() const { return currentCooldown; }
int Player::getXPNeeded() const { return level * 100; }

void Player::update(float dt) {
    if (currentCooldown > 0) {
        currentCooldown -= dt;
        if (currentCooldown < 0) currentCooldown = 0;
    }
}

void Player::draw(sf::RenderWindow& window) {
    sf::CircleShape shape(15.f);
    shape.setPosition(position.x - 15.f, position.y - 15.f);
    shape.setFillColor(sf::Color::Blue);
    window.draw(shape);
}
