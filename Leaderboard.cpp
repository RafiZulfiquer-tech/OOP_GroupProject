#include "Leaderboard.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>

// Constructor - creates leaderboard and loads existing scores
Leaderboard::Leaderboard(const std::string& file) : filename(file) {
    loadScores();  // Load scores from file when created
}

// Add a new score to the leaderboard
void Leaderboard::addScore(const std::string& playerName, const std::string& className,
                           int wave, int kills, int level) {
    // Add the new score to the list
    scores.push_back(Score(playerName, className, wave, kills, level));
    
    // Sort so best scores are first
    sortScores();
    
    // Keep only top 10 scores - FIXED
    if (scores.size() > MAX_SCORES) {
        scores.erase(scores.begin() + MAX_SCORES, scores.end());
    }
    
    // Save to file
    saveScores();
}

// Sort scores - highest wave first, then most kills
void Leaderboard::sortScores() {
    std::sort(scores.begin(), scores.end(), 
        [](const Score& a, const Score& b) {
            // If waves are different, higher wave wins
            if (a.wave != b.wave) return a.wave > b.wave;
            // If waves are same, more kills wins
            return a.kills > b.kills;
        });
}

// Load scores from file
void Leaderboard::loadScores() {
    std::ifstream file(filename);  // Open file for reading
    
    // If file doesn't exist, that's okay - we'll create it later
    if (!file.is_open()) {
        std::cout << "No leaderboard file found. Creating new one." << std::endl;
        return;
    }
    
    scores.clear();  // Clear old scores
    
    // Read each score from file
    std::string name, className;
    int wave, kills, level;
    
    // Read one score per line: name class wave kills level
    while (file >> name >> className >> wave >> kills >> level) {
        scores.push_back(Score(name, className, wave, kills, level));
    }
    
    file.close();
    sortScores();  // Sort after loading
}

// Save scores to file
void Leaderboard::saveScores() {
    std::ofstream file(filename);  // Open file for writing
    
    if (!file.is_open()) {
        std::cout << "Error: Could not save leaderboard!" << std::endl;
        return;
    }
    
    // Write each score to file: name class wave kills level
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

// Check if this wave score would make top 10
bool Leaderboard::isTopScore(int wave) const {
    // If we have less than 10 scores, always accept
    if (scores.size() < MAX_SCORES) return true;
    
    // Check if this wave is better than the worst score (last in list)
    return wave > scores.back().wave;
}

// Draw the leaderboard on screen
void Leaderboard::draw(sf::RenderWindow& window, sf::Font& font) {
    // Draw title "LEADERBOARD" at top
    sf::Text title;
    title.setFont(font);
    title.setString("LEADERBOARD");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color(255, 215, 0));  // Gold color
    title.setStyle(sf::Text::Bold);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    title.setPosition(640, 80);  // Center at top
    window.draw(title);
    
    // Column positions (X coordinates)
    float rankX = 120;
    float nameX = 220;
    float classX = 400;
    float waveX = 580;
    float killsX = 720;
    float levelX = 880;
    
    // Draw column headers
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
    
    window.draw(rankHeader);
    window.draw(nameHeader);
    window.draw(classHeader);
    window.draw(waveHeader);
    window.draw(killsHeader);
    window.draw(levelHeader);
    
    // Draw each score
    float startY = 200;      // Y position of first score
    float spacing = 45;      // Space between each score line
    
    // Loop through top 10 scores
    for (size_t i = 0; i < scores.size() && i < MAX_SCORES; ++i) {
        float yPos = startY + i * spacing;
        
        // Color for this rank
        sf::Color textColor;
        if (i == 0) textColor = sf::Color(255, 215, 0);        // 1st = Gold
        else if (i == 1) textColor = sf::Color(192, 192, 192); // 2nd = Silver
        else if (i == 2) textColor = sf::Color(205, 127, 50);  // 3rd = Bronze
        else textColor = sf::Color::White;                      // Rest = White
        
        // Rank
        sf::Text rankText;
        rankText.setFont(font);
        rankText.setString(std::to_string(i + 1) + ".");
        rankText.setCharacterSize(22);
        rankText.setFillColor(textColor);
        rankText.setPosition(rankX, yPos);
        window.draw(rankText);
        
        // Name (truncate to 10 chars)
        sf::Text nameText;
        nameText.setFont(font);
        std::string displayName = scores[i].playerName;
        if (displayName.length() > 10) displayName = displayName.substr(0, 10);
        nameText.setString(displayName);
        nameText.setCharacterSize(22);
        nameText.setFillColor(textColor);
        nameText.setPosition(nameX, yPos);
        window.draw(nameText);
        
        // Class
        sf::Text classText;
        classText.setFont(font);
        classText.setString(scores[i].className);
        classText.setCharacterSize(22);
        classText.setFillColor(textColor);
        classText.setPosition(classX, yPos);
        window.draw(classText);
        
        // Wave
        sf::Text waveText;
        waveText.setFont(font);
        waveText.setString(std::to_string(scores[i].wave));
        waveText.setCharacterSize(22);
        waveText.setFillColor(textColor);
        waveText.setPosition(waveX, yPos);
        window.draw(waveText);
        
        // Kills
        sf::Text killsText;
        killsText.setFont(font);
        killsText.setString(std::to_string(scores[i].kills));
        killsText.setCharacterSize(22);
        killsText.setFillColor(textColor);
        killsText.setPosition(killsX, yPos);
        window.draw(killsText);
        
        // Level
        sf::Text levelText;
        levelText.setFont(font);
        levelText.setString(std::to_string(scores[i].level));
        levelText.setCharacterSize(22);
        levelText.setFillColor(textColor);
        levelText.setPosition(levelX, yPos);
        window.draw(levelText);
    }
    
    // Draw instructions at bottom
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Press ESC to return to menu");
    instructions.setCharacterSize(24);
    instructions.setFillColor(sf::Color(150, 150, 150));
    sf::FloatRect instrBounds = instructions.getLocalBounds();
    instructions.setOrigin(instrBounds.width / 2, instrBounds.height / 2);
    instructions.setPosition(640, 650);  // Center at bottom
    window.draw(instructions);
}