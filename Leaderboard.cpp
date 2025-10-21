#include "Leaderboard.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>

// Constructor - creates leaderboard and loads existing scores from file
Leaderboard::Leaderboard(const std::string& file) : filename(file) {
    loadScores();  // Load scores from file when object is created
}

// Add a new score entry to the leaderboard
void Leaderboard::addScore(const std::string& playerName, const std::string& className,
                           int wave, int kills, int level) {
    // Add the new score to the scores vector
    scores.push_back(Score(playerName, className, wave, kills, level));
    
    // Sort the scores so the best scores appear first
    sortScores();
    
    // Keep only the top MAX_SCORES (e.g. 10)
    if (scores.size() > MAX_SCORES) {
        scores.erase(scores.begin() + MAX_SCORES, scores.end());
    }
    
    // Save the updated scores list back to the file
    saveScores();
}

// Sort scores primarily by wave (descending), then kills (descending)
void Leaderboard::sortScores() {
    std::sort(scores.begin(), scores.end(), 
        [](const Score& a, const Score& b) {
            // If waves differ, higher wave wins
            if (a.wave != b.wave) return a.wave > b.wave;
            // If waves are the same, higher kills wins
            return a.kills > b.kills;
        });
}

// Load scores from the file into the scores vector
void Leaderboard::loadScores() {
    std::ifstream file(filename);  // Open the file for reading
    
    // If file doesn't exist yet, print info and return
    if (!file.is_open()) {
        std::cout << "No leaderboard file found. Creating new one." << std::endl;
        return;
    }
    
    scores.clear();  // Clear any existing scores
    
    // Variables to read each line into
    std::string name, className;
    int wave, kills, level;
    
    // Read scores line by line: name class wave kills level
    while (file >> name >> className >> wave >> kills >> level) {
        scores.push_back(Score(name, className, wave, kills, level));
    }
    
    file.close();
    
    // Sort scores after loading to ensure order is correct
    sortScores();
}

// Save current scores vector to the file
void Leaderboard::saveScores() {
    std::ofstream file(filename);  // Open file for writing
    
    // Check if file opened successfully
    if (!file.is_open()) {
        std::cout << "Error: Could not save leaderboard!" << std::endl;
        return;
    }
    
    // Write each score entry in the format: name class wave kills level
    for (const auto& score : scores) {
        file << score.playerName << " " 
             << score.className << " " 
             << score.wave << " " 
             << score.kills << " " 
             << score.level << "\n";
    }
    
    file.close();
    std::cout << "Leaderboard saved!" << std::endl;
}

// Check if a given wave value qualifies as a top score on leaderboard
bool Leaderboard::isTopScore(int wave) const {
    // If fewer than max scores, always qualifies
    if (scores.size() < MAX_SCORES) return true;
    
    // Otherwise check if wave is better than lowest recorded wave (last element)
    return wave > scores.back().wave;
}

// Draw the leaderboard on the SFML window using provided font
void Leaderboard::draw(sf::RenderWindow& window, sf::Font& font) {
    // Draw title "LEADERBOARD" centered at top
    sf::Text title;
    title.setFont(font);
    title.setString("LEADERBOARD");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color(255, 215, 0));  // Gold color
    title.setStyle(sf::Text::Bold);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    title.setPosition(640, 80);  // Centered horizontally at top
    window.draw(title);
    
    // Define X positions for each leaderboard column
    float rankX = 120;
    float nameX = 220;
    float classX = 400;
    float waveX = 580;
    float killsX = 720;
    float levelX = 880;
    
    // Prepare column headers with light gray color
    sf::Text rankHeader, nameHeader, classHeader, waveHeader, killsHeader, levelHeader;
    
    rankHeader.setFont(font);
    rankHeader.setString("Rank");
    rankHeader.setCharacterSize(24);
    rankHeader.setFillColor(sf::Color(200, 200, 200));
    rankHeader.setPosition(rankX, 150);
    
    nameHeader.setFont(font);
    nameHeader.setString("Name");
    nameHeader.setCharacterSize(24);
    nameHeader.setFillColor(sf::Color(200, 200, 200));
    nameHeader.setPosition(nameX, 150);
    
    classHeader.setFont(font);
    classHeader.setString("Class");
    classHeader.setCharacterSize(24);
    classHeader.setFillColor(sf::Color(200, 200, 200));
    classHeader.setPosition(classX, 150);
    
    waveHeader.setFont(font);
    waveHeader.setString("Wave");
    waveHeader.setCharacterSize(24);
    waveHeader.setFillColor(sf::Color(200, 200, 200));
    waveHeader.setPosition(waveX, 150);
    
    killsHeader.setFont(font);
    killsHeader.setString("Kills");
    killsHeader.setCharacterSize(24);
    killsHeader.setFillColor(sf::Color(200, 200, 200));
    killsHeader.setPosition(killsX, 150);
    
    levelHeader.setFont(font);
    levelHeader.setString("Level");
    levelHeader.setCharacterSize(24);
    levelHeader.setFillColor(sf::Color(200, 200, 200));
    levelHeader.setPosition(levelX, 150);
    
    // Draw all the headers
    window.draw(rankHeader);
    window.draw(nameHeader);
    window.draw(classHeader);
    window.draw(waveHeader);
    window.draw(killsHeader);
    window.draw(levelHeader);
    
    // Starting Y position and vertical spacing for each score row
    float startY = 200;
    float spacing = 45;
    
    // Loop through top scores to display them
    for (size_t i = 0; i < scores.size() && i < MAX_SCORES; ++i) {
        float yPos = startY + i * spacing;
        
        // Set text color based on rank: Gold, Silver, Bronze, or White
        sf::Color textColor;
        if (i == 0) textColor = sf::Color(255, 215, 0);        // 1st place = Gold
        else if (i == 1) textColor = sf::Color(192, 192, 192); // 2nd place = Silver
        else if (i == 2) textColor = sf::Color(205, 127, 50);  // 3rd place = Bronze
        else textColor = sf::Color::White;                      // Others = White
        
        // Draw Rank number
        sf::Text rankText;
        rankText.setFont(font);
        rankText.setString(std::to_string(i + 1) + ".");
        rankText.setCharacterSize(22);
        rankText.setFillColor(textColor);
        rankText.setPosition(rankX, yPos);
        window.draw(rankText);
        
        // Draw Player name, truncated to 10 characters if too long
        sf::Text nameText;
        nameText.setFont(font);
        std::string displayName = scores[i].playerName;
        if (displayName.length() > 10) displayName = displayName.substr(0, 10);
        nameText.setString(displayName);
        nameText.setCharacterSize(22);
        nameText.setFillColor(textColor);
        nameText.setPosition(nameX, yPos);
        window.draw(nameText);
        
        // Draw Player class name
        sf::Text classText;
        classText.setFont(font);
        classText.setString(scores[i].className);
        classText.setCharacterSize(22);
        classText.setFillColor(textColor);
        classText.setPosition(classX, yPos);
        window.draw(classText);
        
        // Draw Wave reached
        sf::Text waveText;
        waveText.setFont(font);
        waveText.setString(std::to_string(scores[i].wave));
        waveText.setCharacterSize(22);
        waveText.setFillColor(textColor);
        waveText.setPosition(waveX, yPos);
        window.draw(waveText);
        
        // Draw Kills count
        sf::Text killsText;
        killsText.setFont(font);
        killsText.setString(std::to_string(scores[i].kills));
        killsText.setCharacterSize(22);
        killsText.setFillColor(textColor);
        killsText.setPosition(killsX, yPos);
        window.draw(killsText);
        
        // Draw Level reached
        sf::Text levelText;
        levelText.setFont(font);
        levelText.setString(std::to_string(scores[i].level));
        levelText.setCharacterSize(22);
        levelText.setFillColor(textColor);
        levelText.setPosition(levelX, yPos);
        window.draw(levelText);
    }
    
    // Draw instructions at the bottom center of the screen
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Press ESC to return to menu");
    instructions.setCharacterSize(24);
    instructions.setFillColor(sf::Color(150, 150, 150));
    sf::FloatRect instrBounds = instructions.getLocalBounds();
    instructions.setOrigin(instrBounds.width / 2, instrBounds.height / 2);
    instructions.setPosition(640, 650);  // Center horizontally near bottom
    window.draw(instructions);
}