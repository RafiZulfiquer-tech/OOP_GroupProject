#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Enum representing different menu and game states
enum class MenuState {
    MAIN_MENU,     // Main menu screen
    CLASS_SELECT,  // Character class selection screen
    SETTINGS,      // Settings menu (not yet implemented)
    LEADERBOARD,   // Leaderboard screen
    PLAYING,       // Gameplay state
    PAUSED,        // Pause menu during gameplay
    GAME_OVER      // Game over screen
};

class Menu {
private:
    MenuState currentState;  // Current active menu or game state
    sf::Font font;           // Font used for all menu texts

    // Main menu items (Start Game, Leaderboard, Quit)
    std::vector<sf::Text> mainMenuItems;
    int selectedMainMenuItem;  // Index of selected main menu item (-1 if none)

    // Class selection menu items (Warrior, Wizard, Rogue)
    std::vector<sf::Text> classSelectItems;
    int selectedClass;  // Index of selected class (-1 if none)

    sf::Text titleText;               // Title text for main menu ("GOBLIN SLAYER")
    sf::RectangleShape background;   // Background rectangle for menu (semi-transparent)

public:
    Menu();  // Constructor: initializes menu state and background

    // Load font from a file; returns false if loading fails
    bool loadFont(const std::string& fontPath);

    // Get current menu or game state
    MenuState getCurrentState() const { return currentState; }
    
    // Change current state and reset selection indices
    void setState(MenuState state);
    
    // Set the font externally (for example, if already loaded elsewhere)
    void setFont(const sf::Font& font);

    // Handle mouse movement for hover effects on menu items
    void handleMouseMove(sf::Vector2f mousePos);

    // Handle mouse clicks, returns selected item index or -1 if none
    int handleClick(sf::Vector2f mousePos);

    // Draw the menu items and background on the given render window
    void draw(sf::RenderWindow& window);

    // Get the index of the selected class in class select menu
    int getSelectedClass() const { return selectedClass; }

private:
    // Setup text items for the main menu
    void setupMainMenu();

    // Setup text items for the class selection menu
    void setupClassSelect();

    // Helper function to check if mouse is over a specific text item
    bool isMouseOver(const sf::Text& text, sf::Vector2f mousePos) const;
};

#endif