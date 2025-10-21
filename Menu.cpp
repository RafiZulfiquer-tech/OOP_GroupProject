#include "Menu.h"

// Constructor: Initialize menu with default state and set up background
Menu::Menu() : currentState(MenuState::MAIN_MENU), selectedMainMenuItem(-1), selectedClass(-1) {
    // Set background size to cover the window (1280x720)
    background.setSize(sf::Vector2f(1280, 720));
    // Set background color with some transparency (RGBA)
    background.setFillColor(sf::Color(20, 20, 30, 200));
}

// Load the font from a file, return false if failed
bool Menu::loadFont(const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        return false;  // Failed to load font
    }
    // Setup the menu items after loading font
    setupMainMenu();
    setupClassSelect();
    return true;
}

// Setup the main menu items (title + options)
void Menu::setupMainMenu() {
    mainMenuItems.clear();  // Clear previous items
    
    // Configure title text properties
    titleText.setFont(font);
    titleText.setString("GOBLIN SLAYER");
    titleText.setCharacterSize(72);
    titleText.setFillColor(sf::Color(200, 50, 50));  // Red color
    titleText.setStyle(sf::Text::Bold);

    // Center title by origin, position it at top center of screen
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    titleText.setPosition(640, 150);

    // Define main menu options (no settings option here)
    std::vector<std::string> options = {"Start Game", "Leaderboard", "Quit"};
    float startY = 350;   // Starting Y position for menu items
    float spacing = 80;   // Vertical spacing between items
    
    // Create each menu option as sf::Text
    for (size_t i = 0; i < options.size(); i++) {
        sf::Text item;
        item.setFont(font);
        item.setString(options[i]);
        item.setCharacterSize(40);
        item.setFillColor(sf::Color::White);

        // Center the item horizontally
        sf::FloatRect bounds = item.getLocalBounds();
        item.setOrigin(bounds.width / 2, bounds.height / 2);
        item.setPosition(640, startY + i * spacing);

        mainMenuItems.push_back(item);
    }
}

// Setup the class selection menu items
void Menu::setupClassSelect() {
    classSelectItems.clear();

    // Class names and their corresponding colors
    std::vector<std::string> classes = {"WARRIOR", "WIZARD", "ROGUE"};
    std::vector<sf::Color> colors = {
        sf::Color(200, 50, 50),   // Red for Warrior
        sf::Color(50, 100, 200),  // Blue for Wizard
        sf::Color(50, 200, 50)    // Green for Rogue
    };

    float startY = 300;  // Starting Y position for class items
    float spacing = 120; // Spacing between class items

    // Create each class option as sf::Text
    for (size_t i = 0; i < classes.size(); i++) {
        sf::Text item;
        item.setFont(font);
        item.setString(classes[i]);
        item.setCharacterSize(50);
        item.setFillColor(colors[i]);
        item.setStyle(sf::Text::Bold);

        // Center the item horizontally
        sf::FloatRect bounds = item.getLocalBounds();
        item.setOrigin(bounds.width / 2, bounds.height / 2);
        item.setPosition(640, startY + i * spacing);

        classSelectItems.push_back(item);
    }
}

// Change current menu state and reset selection indices
void Menu::setState(MenuState state) {
    currentState = state;
    selectedMainMenuItem = -1;  // Reset selected main menu item
    selectedClass = -1;         // Reset selected class index
}

// Helper function to check if mouse is over a given sf::Text item
bool Menu::isMouseOver(const sf::Text& text, sf::Vector2f mousePos) const {
    sf::FloatRect bounds = text.getGlobalBounds();  // Get global bounds of text
    return bounds.contains(mousePos);  // True if mouse inside bounds
}

// Handle mouse movement to highlight hovered items
void Menu::handleMouseMove(sf::Vector2f mousePos) {
    if (currentState == MenuState::MAIN_MENU) {
        // For each main menu item, check if hovered and update appearance
        for (size_t i = 0; i < mainMenuItems.size(); i++) {
            if (isMouseOver(mainMenuItems[i], mousePos)) {
                mainMenuItems[i].setFillColor(sf::Color::Yellow);  // Highlight color
                mainMenuItems[i].setScale(1.1f, 1.1f);              // Slightly enlarge
            } else {
                mainMenuItems[i].setFillColor(sf::Color::White);   // Default color
                mainMenuItems[i].setScale(1.0f, 1.0f);             // Normal size
            }
        }
    } else if (currentState == MenuState::CLASS_SELECT) {
        // Base colors for each class (to reset when not hovered)
        std::vector<sf::Color> baseColors = {
            sf::Color(200, 50, 50),
            sf::Color(50, 100, 200),
            sf::Color(50, 200, 50)
        };

        // For each class item, check hover and update color & size
        for (size_t i = 0; i < classSelectItems.size(); i++) {
            if (isMouseOver(classSelectItems[i], mousePos)) {
                classSelectItems[i].setFillColor(sf::Color::Yellow);  // Highlight
                classSelectItems[i].setScale(1.2f, 1.2f);              // Enlarge more
            } else {
                classSelectItems[i].setFillColor(baseColors[i]);      // Reset color
                classSelectItems[i].setScale(1.0f, 1.0f);             // Normal size
            }
        }
    }
}

// Handle mouse click, return selected menu or class index or -1 if none
int Menu::handleClick(sf::Vector2f mousePos) {
    if (currentState == MenuState::MAIN_MENU) {
        // Check each main menu item, return index if clicked
        for (size_t i = 0; i < mainMenuItems.size(); i++) {
            if (isMouseOver(mainMenuItems[i], mousePos)) {
                return static_cast<int>(i);  // 0=Start, 1=Leaderboard, 2=Quit
            }
        }
    } else if (currentState == MenuState::CLASS_SELECT) {
        // Check each class item, store selection and return index if clicked
        for (size_t i = 0; i < classSelectItems.size(); i++) {
            if (isMouseOver(classSelectItems[i], mousePos)) {
                selectedClass = static_cast<int>(i);
                return selectedClass;
            }
        }
    }
    return -1;  // Nothing selected
}

// Draw menu items on the window based on current state
void Menu::draw(sf::RenderWindow& window) {
    window.draw(background);  // Draw semi-transparent background
    
    if (currentState == MenuState::MAIN_MENU) {
        window.draw(titleText);  // Draw game title
        for (auto& item : mainMenuItems) {
            window.draw(item);    // Draw each main menu option
        }
    } else if (currentState == MenuState::CLASS_SELECT) {
        // Draw class select title
        sf::Text selectTitle;
        selectTitle.setFont(font);
        selectTitle.setString("SELECT YOUR CLASS");
        selectTitle.setCharacterSize(60);
        selectTitle.setFillColor(sf::Color::White);
        selectTitle.setStyle(sf::Text::Bold);
        sf::FloatRect bounds = selectTitle.getLocalBounds();
        selectTitle.setOrigin(bounds.width / 2, bounds.height / 2);
        selectTitle.setPosition(640, 150);
        window.draw(selectTitle);
        
        // Draw each class option
        for (auto& item : classSelectItems) {
            window.draw(item);
        }
    }
}

// Set font externally and reset menu items accordingly
void Menu::setFont(const sf::Font& fontRef) {
    font = fontRef;
    setupMainMenu();     // Refresh main menu text with new font
    setupClassSelect();  // Refresh class select text with new font
}