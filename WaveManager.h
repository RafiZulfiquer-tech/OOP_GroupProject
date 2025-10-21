#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

#include "Environment.h"
#include "Goblin.h"
#include "GoblinBrute.h"
#include "GoblinLord.h"

class WaveManager {
public:
    WaveManager(Environment* env);

    void update(float dt);
    int getCurrentWave() const;
    bool isWaveActive() const;

private:
    void startNextWave();

    Environment* environment;
    int currentWave;
    float waveTimer;
    bool waveActive;
    int enemiesToSpawn;
};

#endif