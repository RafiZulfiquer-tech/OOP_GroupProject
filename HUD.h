#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>

class HUD {
public:
    HUD(sf::Font& font);

    void update(int wave, int playerHealth, int playerMaxHealth, 
                int kills, int xp, int xpNeeded, int level, const std::string& className);
    void draw(sf::RenderWindow& window);

private:
    sf::Text waveText;
    sf::Text healthText;
    sf::Text killsText;
    sf::Text xpText;
    sf::Text levelText;
    sf::Text classText;
};

#endif // HUD_H