#include "Goblin.h"

// Create Goblin with position, stats, and XP reward
Goblin::Goblin(float x, float y, float hp, float speed, float damage)
    : Enemy(x, y, hp, speed, damage, 10) { // 10 XP reward
    radius = 12.f; // Set goblin's visual size
}

// Draw goblin as a brown circle
void Goblin::draw(sf::RenderWindow& window) {
    sf::CircleShape shape(radius);
    shape.setPosition(position.x - radius, position.y - radius);
    shape.setFillColor(sf::Color(139, 69, 19)); // Brown
    window.draw(shape);
}