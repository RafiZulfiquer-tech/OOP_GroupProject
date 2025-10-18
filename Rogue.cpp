#include "Rogue.h"
#include "Attack.h"
#include <cmath>
#include <cstdlib>

Rogue::Rogue(float x, float y)
    : Player(x, y, "Rogue"), daggerSpeed(450.f), daggerDamage(20), critChance(0.15f) {
    attackCooldown = 0.3f;
}

std::unique_ptr<Attack> Rogue::createAttack(float angleToMouse) {
    int dmg = calculateDamage();
    
    float angleRad = angleToMouse * 3.14159f / 180.f;
    
    sf::Vector2f vel(
        std::cos(angleRad) * daggerSpeed,
        std::sin(angleRad) * daggerSpeed
    );
    
    return std::make_unique<DaggerAttack>(dmg, 800.f, position, vel, 7.f);
}

void Rogue::evolve() { evolved = true; }
float Rogue::getCritChance() const { return critChance; }

int Rogue::calculateDamage() const {
    if (static_cast<float>(rand()) / RAND_MAX < critChance)
        return daggerDamage * 2;
    return daggerDamage;
}

void Rogue::draw(sf::RenderWindow& window) {
    sf::CircleShape shape(15.f);
    shape.setPosition(position.x - 15.f, position.y - 15.f);
    shape.setFillColor(sf::Color(255, 165, 0));
    shape.setOutlineColor(sf::Color(200, 120, 0));
    shape.setOutlineThickness(2.f);
    window.draw(shape);
}