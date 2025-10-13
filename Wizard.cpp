#include "Wizard.h"
#include "Attack.h"
#include <cmath>

Wizard::Wizard(float x, float y)
    : Player(x, y, "Wizard"), mana(100), maxMana(100), manaRegen(15.f), boltDamage(35) {
    attackCooldown = 0.4f;
}

std::unique_ptr<Attack> Wizard::createAttack(float angleToMouse) {
    if (hasMana(10)) {
        consumeMana(10);
        
        float angleRad = angleToMouse * 3.14159f / 180.f;
        float boltSpeed = 500.f;
        
        sf::Vector2f vel(
            std::cos(angleRad) * boltSpeed,
            std::sin(angleRad) * boltSpeed
        );
        
        return std::make_unique<ProjectileAttack>(boltDamage, 1000.f, position, vel, 10.f);
    }
    return nullptr;
}

void Wizard::evolve() { evolved = true; }

void Wizard::update(float dt) {
    Player::update(dt);
    mana = std::min(maxMana, mana + static_cast<int>(manaRegen * dt));
}

void Wizard::draw(sf::RenderWindow& window) {
    sf::CircleShape shape(15.f);
    shape.setPosition(position.x - 15.f, position.y - 15.f);
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineColor(sf::Color(0, 0, 150));
    shape.setOutlineThickness(2.f);
    window.draw(shape);
}

int Wizard::getMana() const { return mana; }
int Wizard::getMaxMana() const { return maxMana; }
bool Wizard::hasMana(int cost) const { return mana >= cost; }
void Wizard::consumeMana(int cost) { mana = std::max(0, mana - cost); }
