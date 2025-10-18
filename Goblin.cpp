#include "Goblin.h"

Goblin::Goblin(float x, float y, float hp, float speed, float damage)
    : Enemy(x, y, hp, speed, damage, 10) { // 10 is attack cooldown
    radius = 12.f;
}

void Goblin::draw(sf::RenderWindow& window) {
    sf::CircleShape shape(radius);
    shape.setPosition(position.x - radius, position.y - radius);
    shape.setFillColor(sf::Color(139, 69, 19));
    window.draw(shape);
}
