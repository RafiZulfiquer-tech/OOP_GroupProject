#include "Warrior.h"
#include "Attack.h"
#include <cmath>

Warrior::Warrior(float x, float y)
    : Player(x, y, "Warrior"), meleeDamage(20.f), meleeRange(50.f) {
    attackCooldown = 0.3f;
    currentCooldown = 0.f;
}

std::unique_ptr<Attack> Warrior::createAttack(float angleToMouse) {
    return std::make_unique<SlashAttack>(
        static_cast<int>(meleeDamage),
        meleeRange,
        position,
        angleToMouse
    );
}

void Warrior::evolve() { evolved = true; }
float Warrior::getMeleeDamage() const { return meleeDamage; }
float Warrior::getMeleeRange() const { return meleeRange; }

void Warrior::draw(sf::RenderWindow& window) {
    sf::CircleShape shape(15.f);
    shape.setPosition(position.x - 15.f, position.y - 15.f);
    shape.setFillColor(sf::Color::Red);
    shape.setOutlineColor(sf::Color(150, 0, 0));
    shape.setOutlineThickness(2.f);
    window.draw(shape);
}
