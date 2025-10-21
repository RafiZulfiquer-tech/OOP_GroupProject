#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

// A single score entry - stores one player's game result
struct Score {
    std::string playerName;  // Player's name
    std::string className;   // Player's class (e.g., Warrior, Wizard, Rogue)
    int wave;                // Wave number reached
    int kills;               // Number of enemies killed
    int level;               // Player's level at end of game
    
    // Constructor - initializes all member variables
    Score(const std::string& name, const std::string& cls, int w, int k, int lvl)
        : playerName(name), className(cls), wave(w), kills(k), level(lvl) {}
};

// Leaderboard class - manages and displays top scores
class Leaderboard {
private:
    std::vector<Score> scores;         // Container for all scores loaded or added
    const size_t MAX_SCORES = 10;      // Maximum number of top scores to keep
    std::string filename;              // Filename for saving/loading leaderboard
    
public:
    // Constructor - optionally takes filename, loads existing scores from file
    Leaderboard(const std::string& file = "leaderboard.txt");
    
    // Adds a new score entry to the leaderboard
    void addScore(const std::string& playerName, const std::string& className, 
                  int wave, int kills, int level);
    
    // Loads scores from the file into the scores vector
    void loadScores();
    
    // Saves current scores vector to the file
    void saveScores();
    
    // Draws the leaderboard on the given SFML window with the given font
    void draw(sf::RenderWindow& window, sf::Font& font);
    
    // Returns true if the given wave value qualifies as a top score
    bool isTopScore(int wave) const;
    
private:
    // Sorts the scores vector by wave (descending), then kills (descending)
    void sortScores();
};

#endif // LEADERBOARD_H