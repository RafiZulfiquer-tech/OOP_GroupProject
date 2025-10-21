#include "Warrior.h"
#include "Attack.h"
#include <cmath>

// Constructor initializes position, class name, and warrior-specific stats
Warrior::Warrior(float x, float y)
    : Player(x, y, "Warrior"), meleeDamage(20.f), meleeRange(50.f) {
    attackCooldown = 0.3f;
    currentCooldown = 0.f;
}

// Create a melee slash attack at the given angle
std::unique_ptr<Attack> Warrior::createAttack(float angleToMouse) {
    return std::make_unique<SlashAttack>(
        static_cast<int>(meleeDamage), // Damage as int
        meleeRange,                    // Attack range
        position,                     // Player position
        angleToMouse                 // Attack angle in degrees
    );
}

// Mark warrior as evolved (expandable for special effects)
void Warrior::evolve() { evolved = true; }

// Get melee damage amount
float Warrior::getMeleeDamage() const { return meleeDamage; }

// Get melee attack range
float Warrior::getMeleeRange() const { return meleeRange; }

// Draw the warrior as a red circle with a dark red outline
void Warrior::draw(sf::RenderWindow& window) {
    sf::CircleShape shape(15.f);
    shape.setPosition(position.x - 15.f, position.y - 15.f);
    shape.setFillColor(sf::Color::Red);
    shape.setOutlineColor(sf::Color(150, 0, 0));
    shape.setOutlineThickness(2.f);
    window.draw(shape);
}