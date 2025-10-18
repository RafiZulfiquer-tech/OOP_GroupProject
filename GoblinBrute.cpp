#include "GoblinBrute.h"
#include <algorithm>
#include <stdexcept>

GoblinBrute::GoblinBrute(float x, float y, float hp, float speed, float damage)
    : Enemy(x, y, hp, speed, damage, 25), armor(10), baseArmor(10) {
    radius = 18.f;
}

void GoblinBrute::takeDamage(int dmg) {
    if (dmg < 0) throw std::invalid_argument("Damage cannot be negative");
    int reducedDamage = std::max(1, dmg - armor);
    Entity::takeDamage(reducedDamage);
    armor = std::max(0, armor - 1);
}

void GoblinBrute::draw(sf::RenderWindow& window) {
    sf::CircleShape shape(radius);
    shape.setPosition(position.x - radius, position.y - radius);
    shape.setFillColor(sf::Color(180, 50, 50)); // Brute red

    shape.setOutlineThickness(5.f);
    shape.setOutlineColor(sf::Color::Black);

    window.draw(shape);

    // Draw armour
    sf::CircleShape armorShape(radius * 0.6f);
    armorShape.setPosition(position.x - radius * 0.6f, position.y - radius * 0.6f);
    armorShape.setFillColor(sf::Color(120, 120, 120, 180));
    window.draw(armorShape);
}
