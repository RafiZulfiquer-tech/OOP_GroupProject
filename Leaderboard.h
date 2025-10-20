#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

// A single score entry - stores one player's game result
struct Score {
    std::string playerName;  // Player's name
    std::string className;   // Warrior, Wizard, or Rogue
    int wave;                // What wave they reached
    int kills;               // How many enemies killed
    int level;               // Player level achieved
    
    // Constructor - creates a new score
    Score(const std::string& name, const std::string& cls, int w, int k, int lvl)
        : playerName(name), className(cls), wave(w), kills(k), level(lvl) {}
};

// Leaderboard class - manages the top 10 scores
class Leaderboard {
private:
    std::vector<Score> scores;     // List of all scores
    const size_t MAX_SCORES = 10;  // Keep only top 10 (changed to size_t)
    std::string filename;          // File to save/load from

public:
    // Constructor - loads scores from file
    Leaderboard(const std::string& file = "leaderboard.txt");
    
    // Add a new score to the leaderboard
    void addScore(const std::string& playerName, const std::string& className, 
                  int wave, int kills, int level);
    
    // Load scores from file
    void loadScores();
    
    // Save scores to file
    void saveScores();
    
    // Draw leaderboard on screen
    void draw(sf::RenderWindow& window, sf::Font& font);
    
    // Check if this wave score makes the top 10
    bool isTopScore(int wave) const;
    
private:
    // Sort scores by wave (highest first)
    void sortScores();
};

#endif // LEADERBOARD_H