#include "Menu.h"

Menu::Menu() : currentState(MenuState::MAIN_MENU), selectedMainMenuItem(-1), selectedClass(-1) {
    background.setSize(sf::Vector2f(1280, 720));
    background.setFillColor(sf::Color(20, 20, 30, 200));
}

bool Menu::loadFont(const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        return false;
    }
    setupMainMenu();
    setupClassSelect();
    return true;
}

void Menu::setupMainMenu() {
    mainMenuItems.clear();
    
    // Title
    titleText.setFont(font);
    titleText.setString("GOBLIN SLAYER");
    titleText.setCharacterSize(72);
    titleText.setFillColor(sf::Color(200, 50, 50));
    titleText.setStyle(sf::Text::Bold);
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    titleText.setPosition(640, 150);
    
    // Menu options
    std::vector<std::string> options = {"Start Game", "Settings", "Leaderboard", "Quit"};
    float startY = 350;
    float spacing = 80;
    
    for (size_t i = 0; i < options.size(); i++) {
        sf::Text item;
        item.setFont(font);
        item.setString(options[i]);
        item.setCharacterSize(40);
        item.setFillColor(sf::Color::White);
        
        sf::FloatRect bounds = item.getLocalBounds();
        item.setOrigin(bounds.width / 2, bounds.height / 2);
        item.setPosition(640, startY + i * spacing);
        
        mainMenuItems.push_back(item);
    }
}

void Menu::setupClassSelect() {
    classSelectItems.clear();
    
    // Class options
    std::vector<std::string> classes = {"WARRIOR", "WIZARD", "ROGUE"};
    std::vector<sf::Color> colors = {
        sf::Color(200, 50, 50),   // Red
        sf::Color(50, 100, 200),  // Blue
        sf::Color(50, 200, 50)    // Green
    };
    
    float startY = 300;
    float spacing = 120;
    
    for (size_t i = 0; i < classes.size(); i++) {
        sf::Text item;
        item.setFont(font);
        item.setString(classes[i]);
        item.setCharacterSize(50);
        item.setFillColor(colors[i]);
        item.setStyle(sf::Text::Bold);
        
        sf::FloatRect bounds = item.getLocalBounds();
        item.setOrigin(bounds.width / 2, bounds.height / 2);
        item.setPosition(640, startY + i * spacing);
        
        classSelectItems.push_back(item);
    }
}

void Menu::setState(MenuState state) {
    currentState = state;
    selectedMainMenuItem = -1;
    selectedClass = -1;
}

bool Menu::isMouseOver(const sf::Text& text, sf::Vector2f mousePos) const {
    sf::FloatRect bounds = text.getGlobalBounds();
    return bounds.contains(mousePos);
}

void Menu::handleMouseMove(sf::Vector2f mousePos) {
    if (currentState == MenuState::MAIN_MENU) {
        for (size_t i = 0; i < mainMenuItems.size(); i++) {
            if (isMouseOver(mainMenuItems[i], mousePos)) {
                mainMenuItems[i].setFillColor(sf::Color::Yellow);
                mainMenuItems[i].setScale(1.1f, 1.1f);
            } else {
                mainMenuItems[i].setFillColor(sf::Color::White);
                mainMenuItems[i].setScale(1.0f, 1.0f);
            }
        }
    } else if (currentState == MenuState::CLASS_SELECT) {
        std::vector<sf::Color> baseColors = {
            sf::Color(200, 50, 50),
            sf::Color(50, 100, 200),
            sf::Color(50, 200, 50)
        };
        
        for (size_t i = 0; i < classSelectItems.size(); i++) {
            if (isMouseOver(classSelectItems[i], mousePos)) {
                classSelectItems[i].setFillColor(sf::Color::Yellow);
                classSelectItems[i].setScale(1.2f, 1.2f);
            } else {
                classSelectItems[i].setFillColor(baseColors[i]);
                classSelectItems[i].setScale(1.0f, 1.0f);
            }
        }
    }
}

int Menu::handleClick(sf::Vector2f mousePos) {
    if (currentState == MenuState::MAIN_MENU) {
        for (size_t i = 0; i < mainMenuItems.size(); i++) {
            if (isMouseOver(mainMenuItems[i], mousePos)) {
                return static_cast<int>(i);  // 0=Start, 1=Settings, 2=Leaderboard, 3=Quit
            }
        }
    } else if (currentState == MenuState::CLASS_SELECT) {
        for (size_t i = 0; i < classSelectItems.size(); i++) {
            if (isMouseOver(classSelectItems[i], mousePos)) {
                selectedClass = static_cast<int>(i);
                return selectedClass;
            }
        }
    }
    return -1;
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(background);
    
    if (currentState == MenuState::MAIN_MENU) {
        window.draw(titleText);
        for (auto& item : mainMenuItems) {
            window.draw(item);
        }
    } else if (currentState == MenuState::CLASS_SELECT) {
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
        
        for (auto& item : classSelectItems) {
            window.draw(item);
        }
    }
}

void Menu::setFont(const sf::Font& fontRef) {
    font = fontRef;
    setupMainMenu();
    setupClassSelect();
}