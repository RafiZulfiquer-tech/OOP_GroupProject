#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum class MenuState{
    MAIN_MENU,
    CLASS_SELECT,
    SETTINGS,
    LEADERBOARD,
    PLAYING,
    PAUSED,
    GAME_OVER
};

class Menu {
    private:
    MenuState currentState;
    sf::Font font;

    // main menu
    std::vector<sf::Text> mainMenuItems;
    int selectedMainMenuItem;

    //class select
    std::vector <sf::Text> classSelectItems;
    int selectedClass;

    sf::Text titleText;
    sf::RectangleShape background;

    public:
    Menu();
    bool loadFont(const std::string& fontPath);

    //state management
    MenuState getCurrentState() const { return currentState; }
    void setState(MenuState state);

    void handleMouseMove(sf::Vector2f mousePos);
    int handleClick(sf::Vector2f mousePos);
    void draw(sf::RenderWindow& window);

    //get selected class
    int getSelectedClass() const { return selectedClass; }

    private:
    void setupMainMenu();
    void setupClassSelect();
    bool isMouseOver(const sf::Text& text, sf::Vector2f mousePos) const;
};


#endif