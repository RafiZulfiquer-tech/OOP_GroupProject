#include "Leaderboard.h"
#include <fstream>
#include <algorithm>
#include <iostream>

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
    
    // Draw column headers
    sf::Text headers;
    headers.setFont(font);
    headers.setString("Rank    Name         Class      Wave    Kills    Level");
    headers.setCharacterSize(24);
    headers.setFillColor(sf::Color(200, 200, 200));
    headers.setPosition(100, 150);
    window.draw(headers);
    
    // Draw each score
    float startY = 200;      // Y position of first score
    float spacing = 45;      // Space between each score line
    
    // Loop through top 10 scores
    for (size_t i = 0; i < scores.size() && i < MAX_SCORES; ++i) {
        sf::Text scoreText;
        scoreText.setFont(font);
        
        // Rank number (1, 2, 3, etc)
        std::string rankStr = std::to_string(i + 1);
        if (i < 9) rankStr = " " + rankStr;  // Add space for single digits
        
        // Player name (limit to 10 characters)
        std::string nameStr = scores[i].playerName;
        if (nameStr.length() > 10) nameStr = nameStr.substr(0, 10);
        while (nameStr.length() < 10) nameStr += " ";  // Pad with spaces
        
        // Class name
        std::string classStr = scores[i].className;
        while (classStr.length() < 10) classStr += " ";  // Pad with spaces
        
        // Build the full line of text
        std::string line = rankStr + ".    " + nameStr + "   " + classStr + "   " +
                          std::to_string(scores[i].wave) + "       " +
                          std::to_string(scores[i].kills) + "        " +
                          std::to_string(scores[i].level);
        
        scoreText.setString(line);
        scoreText.setCharacterSize(22);
        
        // Color top 3 differently
        if (i == 0) scoreText.setFillColor(sf::Color(255, 215, 0));      // 1st = Gold
        else if (i == 1) scoreText.setFillColor(sf::Color(192, 192, 192)); // 2nd = Silver
        else if (i == 2) scoreText.setFillColor(sf::Color(205, 127, 50));  // 3rd = Bronze
        else scoreText.setFillColor(sf::Color::White);                      // Rest = White
        
        scoreText.setPosition(100, startY + i * spacing);
        window.draw(scoreText);
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