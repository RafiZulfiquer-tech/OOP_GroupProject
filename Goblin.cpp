#include "Goblin.h"

Goblin::Goblin(float x, float y)
    : Enemy(x, y, 50, 80.f, 10, 10) {
    radius = 12.f;
}

void Goblin::draw(sf::RenderWindow& window) {
    sf::CircleShape shape(radius);
    shape.setPosition(position.x - radius, position.y - radius);
    shape.setFillColor(sf::Color(139, 69, 19));
    window.draw(shape);
}
