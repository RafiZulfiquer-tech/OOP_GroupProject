#include "Wizard.h"
#include "Attack.h"
#include <cmath>

// Constructor for Wizard class, initializes position, mana, mana regeneration, and bolt damage
Wizard::Wizard(float x, float y)
    : Player(x, y, "Wizard"),        // Call base class constructor with position and class name
      mana(100),                     // Starting mana
      maxMana(100),                  // Maximum mana
      manaRegen(15.f),               // Mana regeneration rate per second
      boltDamage(35) {               // Damage dealt by magic bolt attack
    attackCooldown = 0.4f;           // Time between attacks (in seconds)
}

// Create a projectile attack (magic bolt) if wizard has enough mana
std::unique_ptr<Attack> Wizard::createAttack(float angleToMouse) {
    if (hasMana(10)) {                // Check if enough mana (10) is available
        consumeMana(0);             // Consume mana cost for the attack

        // Convert attack angle from degrees to radians for trigonometric functions
        float angleRad = angleToMouse * 3.14159f / 180.f;
        float boltSpeed = 500.f;     // Speed of the magic bolt projectile

        // Calculate velocity vector based on angle
        sf::Vector2f vel(
            std::cos(angleRad) * boltSpeed,
            std::sin(angleRad) * boltSpeed
        );

        // Return a new ProjectileAttack instance with damage, range, position, velocity, and size
        return std::make_unique<ProjectileAttack>(boltDamage, 1000.f, position, vel, 10.f);
    }

    // If not enough mana, no attack is created
    return nullptr;
}

// Mark wizard as evolved (called on level-up or similar event)
void Wizard::evolve() { 
    evolved = true; 
}

// Update wizard status every frame (dt = delta time in seconds)
void Wizard::update(float dt) {
    Player::update(dt);              // Call base class update (for cooldowns, etc.)

    // Regenerate mana, ensuring it doesn't exceed maxMana
    mana = std::min(maxMana, mana + static_cast<int>(manaRegen * dt));
}

// Draw the wizard character on the window using a blue circle with dark blue outline
void Wizard::draw(sf::RenderWindow& window) {
    sf::CircleShape shape(15.f);     // Circle with radius 15
    shape.setPosition(position.x - 15.f, position.y - 15.f);  // Center at current position
    shape.setFillColor(sf::Color::Blue);                      // Fill color blue
    shape.setOutlineColor(sf::Color(0, 0, 150));              // Dark blue outline
    shape.setOutlineThickness(2.f);                           // Outline thickness
    window.draw(shape);                                        // Render the shape
}

// Get current mana value
int Wizard::getMana() const { 
    return mana; 
}

// Get maximum mana value
int Wizard::getMaxMana() const { 
    return maxMana; 
}

// Check if wizard has enough mana for an action
bool Wizard::hasMana(int cost) const { 
    return mana >= cost; 
}

// Reduce mana by cost amount, ensuring it doesn't go below zero
void Wizard::consumeMana(int cost) { 
    mana = std::max(0, mana - cost); 
}