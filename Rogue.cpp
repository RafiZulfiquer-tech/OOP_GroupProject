#include "Rogue.h"
#include "Attack.h"
#include <cmath>
#include <cstdlib>  // For rand()

// Constructor: Initialize Rogue with position, class name, and stats specific to Rogue
Rogue::Rogue(float x, float y)
    : Player(x, y, "Rogue"),         // Call Player constructor with class "Rogue"
      daggerSpeed(450.f),            // Speed of the thrown dagger projectile
      daggerDamage(20),              // Base damage of dagger attack
      critChance(0.15f)              // 15% critical hit chance
{
    attackCooldown = 0.3f;           // Faster attack rate for Rogue (0.3 seconds)
}

// Create and return a unique_ptr to a dagger attack aimed at angleToMouse (degrees)
std::unique_ptr<Attack> Rogue::createAttack(float angleToMouse) {
    int dmg = calculateDamage();     // Calculate damage, possibly critical

    // Convert degrees to radians for trig functions
    float angleRad = angleToMouse * 3.14159f / 180.f;

    // Calculate velocity vector based on angle and dagger speed
    sf::Vector2f vel(
        std::cos(angleRad) * daggerSpeed,
        std::sin(angleRad) * daggerSpeed
    );

    // Create a new DaggerAttack with damage, range, start position, velocity, and size
    return std::make_unique<DaggerAttack>(dmg, 800.f, position, vel, 7.f);
}

// Override evolve to mark Rogue as evolved
void Rogue::evolve() {
    evolved = true;
}

// Return the Rogue's critical hit chance
float Rogue::getCritChance() const {
    return critChance;
}

// Calculate damage for the attack, with chance to deal double damage on crit
int Rogue::calculateDamage() const {
    // Generate a random float between 0 and 1, compare with crit chance
    if (static_cast<float>(rand()) / RAND_MAX < critChance)
        return daggerDamage * 2;    // Critical hit: double damage
    return daggerDamage;            // Normal damage otherwise
}

// Draw the Rogue as an orange circle with a dark outline
void Rogue::draw(sf::RenderWindow& window) {
    sf::CircleShape shape(15.f);    // Circle with radius 15
    shape.setPosition(position.x - 15.f, position.y - 15.f);  // Center shape on position
    shape.setFillColor(sf::Color(255, 165, 0));              // Orange fill
    shape.setOutlineColor(sf::Color(200, 120, 0));           // Darker orange outline
    shape.setOutlineThickness(2.f);
    window.draw(shape);
}