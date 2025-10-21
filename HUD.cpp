#include "HUD.h"

// Constructor initializes all HUD elements with the same font and positions them
HUD::HUD(sf::Font& font) {
    // Wave display (top left)
    waveText.setFont(font);
    waveText.setCharacterSize(24);
    waveText.setFillColor(sf::Color::White);
    waveText.setPosition(10, 10);

    // Player health display
    healthText.setFont(font);
    healthText.setCharacterSize(24);
    healthText.setFillColor(sf::Color(255, 100, 100)); // Light red
    healthText.setPosition(10, 40);

    // Kill count display
    killsText.setFont(font);
    killsText.setCharacterSize(24);
    killsText.setFillColor(sf::Color(255, 215, 0)); // Gold
    killsText.setPosition(10, 70);

    // XP display
    xpText.setFont(font);
    xpText.setCharacterSize(24);
    xpText.setFillColor(sf::Color(0, 255, 255)); // Cyan
    xpText.setPosition(10, 100);

    // Player level display
    levelText.setFont(font);
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color(255, 255, 0)); // Yellow
    levelText.setPosition(10, 130);

    // Player class display
    classText.setFont(font);
    classText.setCharacterSize(24);
    classText.setFillColor(sf::Color(200, 200, 200)); // Light gray
    classText.setPosition(10, 160);
}

// Updates all HUD text based on the current game state
void HUD::update(int wave, int playerHealth, int playerMaxHealth, 
                 int kills, int xp, int xpNeeded, int level, const std::string& className) {
    
    // Set text values with current data
    waveText.setString("Wave: " + std::to_string(wave));
    healthText.setString("HP: " + std::to_string(playerHealth) + "/" + std::to_string(playerMaxHealth));
    killsText.setString("Kills: " + std::to_string(kills));
    xpText.setString("XP: " + std::to_string(xp) + "/" + std::to_string(xpNeeded));
    levelText.setString("Level: " + std::to_string(level));
    classText.setString("Class: " + className);
}

// Renders all HUD elements to the window
void HUD::draw(sf::RenderWindow& window) {
    window.draw(waveText);
    window.draw(healthText);
    window.draw(killsText);
    window.draw(xpText);
    window.draw(levelText);
    window.draw(classText);
}