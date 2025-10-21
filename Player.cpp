#include "Player.h"
#include "Attack.h"
#include <iostream>

// Constructor: Initialize player position, class name, and default stats
Player::Player(float x, float y, const std::string& cls)
    : Entity(x, y, 15.f, 100),  // Call Entity constructor: position, radius, maxHealth
      speed(100.f),             // Movement speed
      xp(0),                   // Experience points
      level(1),                // Starting level
      kills(0),                // Kill count
      attackCooldown(1.f),     // Time between attacks (in seconds)
      currentCooldown(0.f),    // Current cooldown timer for attacks
      className(cls),          // Player class name (e.g., Warrior, Wizard)
      evolved(false) {}        // Whether the player has evolved (class upgrade)

// Move player based on direction vector and elapsed time
void Player::move(sf::Vector2f direction, float dt) {
    position += direction * speed * dt;
}

// Check if player can attack (attack cooldown has expired)
bool Player::canAttack() const {
    return currentCooldown <= 0.f;
}

// Create an attack object (to be implemented in derived classes)
std::unique_ptr<Attack> Player::createAttack(float angleToMouse) {
    return nullptr;  // Base Player does not create attacks
}

// Reset the attack cooldown timer after an attack
void Player::resetCooldown() {
    currentCooldown = attackCooldown;
}

// Add experience points, check for level up, increase stats, and evolve if applicable
void Player::addXP(int amount) { 
    xp += amount;
    
    // Level up while enough XP is available
    while (xp >= getXPNeeded()) {
        xp -= getXPNeeded();
        level++;

        // Improve player stats on level up
        maxHealth += 10;
        health = maxHealth;  // Restore health fully on level up
        speed += 2.f;

        std::cout << "LEVEL UP! Now level " << level << std::endl;

        // Evolve player class at level 10 if not already evolved
        if (level == 10 && !evolved) {
            evolve();
            std::cout << className << " evolved!" << std::endl;
        }
    }
}

// Increment kill count by one
void Player::addKill() {
    kills += 1;
}

// Mark the player as evolved (class upgrade)
void Player::evolve() {
    evolved = true;
}

// Getters for various player stats and info
int Player::getLevel() const { return level; }
int Player::getXP() const { return xp; }
int Player::getKills() const { return kills; }
std::string Player::getClassName() const { return className; }
float Player::getSpeed() const { return speed; }
bool Player::isEvolved() const { return evolved; }
float Player::getCooldown() const { return currentCooldown; }

// Calculate XP needed for next level (e.g., level * 100)
int Player::getXPNeeded() const {
    return level * 100;
}

// Update function to decrease attack cooldown timer over time
void Player::update(float dt) {
    if (currentCooldown > 0) {
        currentCooldown -= dt;
        if (currentCooldown < 0)
            currentCooldown = 0;
    }
}

// Draw the player as a simple blue circle at their current position
void Player::draw(sf::RenderWindow& window) {
    sf::CircleShape shape(15.f);  // Circle with radius 15 (same as entity radius)
    shape.setPosition(position.x - 15.f, position.y - 15.f); // Center shape on position
    shape.setFillColor(sf::Color::Blue);
    window.draw(shape);
}