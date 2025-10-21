#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

#include "Environment.h"
#include "Goblin.h"
#include "GoblinBrute.h"
#include "GoblinLord.h"

// Manages enemy waves: spawning and wave progression logic
class WaveManager {
public:
    explicit WaveManager(Environment* env);  // Explicit to prevent implicit conversions

    void update(float dt);          // Updates wave timer and spawns new waves
    int getCurrentWave() const;    // Returns current wave number
    bool isWaveActive() const;     // Returns whether enemies are currently active

private:
    void startNextWave();          // Starts spawning the next wave of enemies

    Environment* environment;      // Pointer to the game environment
    int currentWave;               // Current wave number (starting from 0)
    float waveTimer;               // Timer counting down to next wave spawn
    bool waveActive;               // Whether a wave is currently active (enemies present)
    int enemiesToSpawn;            // Number of enemies to spawn in the current wave
};

#endif // WAVEMANAGER_H