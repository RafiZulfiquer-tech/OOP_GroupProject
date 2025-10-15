#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>

class HUD {
public:
    HUD(sf::Font& font);

    void update(int wave, int playerHealth, int playerMaxHealth);
    void draw(sf::RenderWindow& window);

private:
    sf::Text waveText;
    sf::Text healthText;
};

#endif // HUD_H
