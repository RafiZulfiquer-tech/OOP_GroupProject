#include "HUD.h"

HUD::HUD(sf::Font& font) {
    waveText.setFont(font);
    waveText.setCharacterSize(24);
    waveText.setFillColor(sf::Color::White);
    waveText.setPosition(10, 10);

    healthText.setFont(font);
    healthText.setCharacterSize(24);
    healthText.setFillColor(sf::Color::White);
    healthText.setPosition(10, 40);
}

void HUD::update(int wave, int playerHealth, int playerMaxHealth) {
    waveText.setString("Wave: " + std::to_string(wave));
    healthText.setString("HP: " + std::to_string(playerHealth) + "/" + std::to_string(playerMaxHealth));
}

void HUD::draw(sf::RenderWindow& window) {
    window.draw(waveText);
    window.draw(healthText);
}
