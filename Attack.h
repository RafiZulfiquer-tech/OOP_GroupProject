#ifndef ATTACK_H
#define ATTACK_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <algorithm>

// Abstract base class for all attack types
class Attack
{
protected:
    sf::Vector2f position;          // Where the attack is (x, y coordinates)
    sf::Vector2f velocity;          // How fast and which direction it moves
    int damage;                     // How much damage it deals
    float range;                    // How far it can travel
    float distanceTraveled;         // Tracking how far it's gone
    float radius;                   // Size for collision/drawing
    bool active;                    // Is it still happening?
    float lifetime;                 // How long it's been alive
    float maxLifetime;              // When it expires
    std::vector<void *> hitEnemies; // Prevents hitting same enemy twice

public:
    // attack constructor
    Attack(int dmg, float rng, sf::Vector2f pos, sf::Vector2f vel, float rad, float maxLife)
        : position(pos), velocity(vel), damage(dmg), range(rng),
          distanceTraveled(0.f), radius(rad), active(true),
          lifetime(0.f), maxLifetime(maxLife) {}

    virtual ~Attack() = default;

    // Move attack forward; deactivate if expired
    virtual void update(float dt)
    {
        if (!active)
            return;

        lifetime += dt; // Track how long attack has existed
        float moveDistance = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) * dt;
        position += velocity * dt; // Move the attack
        distanceTraveled += moveDistance;

        if (distanceTraveled >= range || lifetime >= maxLifetime)
            active = false; // Deactivate if too far or too old
    }

    // Virtual functions of attacks
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual bool checkCollision(sf::Vector2f targetPos, float targetRadius) const = 0;
    virtual void onHit() = 0;

    // Getters
    int getDamage() const { return damage; }
    float getRange() const { return range; }
    sf::Vector2f getPosition() const { return position; }
    bool isActive() const { return active; }
    float getRadius() const { return radius; }

    // uses find to see if enemy was already hit, prevents goblin being hit twice by the same attack
    bool hasHit(void *enemyPtr) const
    {
        return std::find(hitEnemies.begin(), hitEnemies.end(), enemyPtr) != hitEnemies.end();
    }
    void markHit(void *enemyPtr) //marks enemy and adds to vector to indicate it was hit.
    {
        hitEnemies.push_back(enemyPtr);
    }

    void setActive(bool val) { active = val; } // allows to turn attack on or off outisde of the class. ex when game ends.

    // Force trigger hit behavior
    void deactivate() { onHit(); } // ranged attack disppears after hit
};

// Warrior: arc-based melee slash attack
class SlashAttack : public Attack
{
private:
    float slashAngle; // Direction of attack in degrees

public:

// attack constructor
    SlashAttack(int dmg, float rng, sf::Vector2f pos, float angle)
        : Attack(dmg, rng, pos, sf::Vector2f(0, 0), 60.f, 0.25f), slashAngle(angle) {}

    // Draws a fading arc
    void draw(sf::RenderWindow &window) override
    {
        if (!active)
            return;

        float progress = lifetime / maxLifetime; // progeress oes grom 0 to 1 for completeness of the animation
        float alpha = static_cast<sf::Uint8>(255 * (1.f - progress)); // alpha goes rom 255 to 0 (visible to invisible, fades as the slash disappears)

        //drawing the shape: esatblishing angles and arc.
        sf::ConvexShape arc;
        int pointCount = 20;
        arc.setPointCount(pointCount + 2);
        arc.setPoint(0, sf::Vector2f(0, 0)); // center point

        float startAngle = (slashAngle - 45.f) * 3.14159f / 180.f;
        float endAngle = (slashAngle + 45.f) * 3.14159f / 180.f;

        // Arc shape around the angle
        for (int i = 0; i <= pointCount; i++)
        {
            float t = static_cast<float>(i) / pointCount;
            float angle = startAngle + t * (endAngle - startAngle);
            float x = std::cos(angle) * radius; //x cordinate
            float y = std::sin(angle) * radius; //y coordinate
            arc.setPoint(i + 1, sf::Vector2f(x, y));
        }

        //Drawing the shape
        arc.setPosition(position);
        arc.setFillColor(sf::Color(255, 200, 50, alpha));
        arc.setOutlineColor(sf::Color(255, 100, 0, alpha));
        arc.setOutlineThickness(3.f);
        window.draw(arc);
    }

    // Checks if target is within arc sector
    bool checkCollision(sf::Vector2f targetPos, float targetRadius) const override
    {
        if (!active)
            return false;

        float dx = targetPos.x - position.x; 
        float dy = targetPos.y - position.y;
        float dist = std::sqrt(dx * dx + dy * dy);
        if (dist > radius + targetRadius)
            return false;

        float targetAngle = std::atan2(dy, dx) * 180.f / 3.14159f; //angle from slash to enemy
        float angleDiff = targetAngle - slashAngle;

        // Normalize angle to [-180, 180], ex 340 deg turns to -20deg
        while (angleDiff > 180.f)
            angleDiff -= 360.f;
        while (angleDiff < -180.f)
            angleDiff += 360.f;

        return std::abs(angleDiff) <= 60.f; //  enemies in +/- 60° arc get hit
    }

    void onHit() override
    {
        // Stays active for short duration
    }
};

// Wizard: magic projectile (e.g. bolt, meteor)
class ProjectileAttack : public Attack
{
public:

//constructor
    ProjectileAttack(int dmg, float rng, sf::Vector2f pos, sf::Vector2f vel, float rad = 10.f)
        : Attack(dmg, rng, pos, vel, rad, 0.5f) {}

    // Draws blue circle
    void draw(sf::RenderWindow &window) override
    {
        if (!active)
            return;

        sf::CircleShape shape(radius);
        shape.setOrigin(radius, radius); 
        shape.setPosition(position);
        shape.setFillColor(sf::Color(100, 150, 255, 220));
        shape.setOutlineColor(sf::Color(50, 100, 200));
        shape.setOutlineThickness(3.f);
        window.draw(shape);
    }

    bool checkCollision(sf::Vector2f targetPos, float targetRadius) const override
    {
        if (!active)
            return false;

        float dx = position.x - targetPos.x;
        float dy = position.y - targetPos.y;
        float distSq = dx * dx + dy * dy; //dist sq
        float radSum = radius + targetRadius; 

        return distSq <= radSum * radSum;
    }

    void onHit() override
    {
        active = false; // Disappear on hit
    }
};

// Rogue: fast dagger projectile
class DaggerAttack : public Attack
{
public:
    DaggerAttack(int dmg, float rng, sf::Vector2f pos, sf::Vector2f vel, float rad = 7.f)
        : Attack(dmg, rng, pos, vel, rad, 0.5f) {}

    // Triangle-shaped projectile
    void draw(sf::RenderWindow &window) override
    {
        if (!active)
            return;

        sf::ConvexShape triangle;
        triangle.setPointCount(3);

        float angle = std::atan2(velocity.y, velocity.x);
        float size = radius * 2.f;

        triangle.setPoint(0, sf::Vector2f(size, 0)); // tip
        triangle.setPoint(1, sf::Vector2f(-size / 2, size / 2)); // bottom left
        triangle.setPoint(2, sf::Vector2f(-size / 2, -size / 2)); // bottom right

        triangle.setPosition(position); // move to daggers position
        triangle.setRotation(angle * 180.f / 3.14159f); // Rotate to face movement direction
        triangle.setFillColor(sf::Color(255, 165, 0, 220));
        triangle.setOutlineColor(sf::Color(200, 100, 0));
        triangle.setOutlineThickness(2.f);
        window.draw(triangle);
    }
// check for collision
    bool checkCollision(sf::Vector2f targetPos, float targetRadius) const override
    {
        if (!active)
            return false;

        float dx = position.x - targetPos.x;
        float dy = position.y - targetPos.y;
        float distSq = dx * dx + dy * dy;
        float radSum = radius + targetRadius;

        return distSq <= radSum * radSum; // circle collision - drawn as triangle but collision is circle same as wizard attack.
    }

    void onHit() override
    {
        active = false;
    }
};

#endif // ATTACK_H