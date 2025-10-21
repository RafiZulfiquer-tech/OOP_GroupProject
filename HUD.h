#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include <string>

// HUD class manages the heads-up display for player info and game state
class HUD {
public:
    // Constructor initializes HUD with a font to use for all text elements
    HUD(sf::Font& font);

    // Update the displayed information with current game stats
    // wave: current wave number
    // playerHealth, playerMaxHealth: current and max health of player
    // kills: number of enemies defeated
    // xp: current experience points
    // xpNeeded: experience points needed for next level
    // level: current player level
    // className: player's class name (e.g. Warrior, Mage)
    void update(int wave, int playerHealth, int playerMaxHealth, 
                int kills, int xp, int xpNeeded, int level, const std::string& className);

    // Draw the HUD elements onto the given render window
    void draw(sf::RenderWindow& window);

private:
    // SFML text objects for displaying various HUD information
    sf::Text waveText;    // Displays current wave number
    sf::Text healthText;  // Displays player health
    sf::Text killsText;   // Displays kill count
    sf::Text xpText;      // Displays experience points
    sf::Text levelText;   // Displays player level
    sf::Text classText;   // Displays player class name
};

#endif // HUD_H