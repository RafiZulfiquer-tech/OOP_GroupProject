#include "WaveManager.h"

#include <cmath>
#include <cstdlib>

WaveManager::WaveManager(Environment* env)
    : environment(env),
      currentWave(0),
      waveTimer(3.0f),    // 3-second delay before the first wave starts
      waveActive(false),
      enemiesToSpawn(0) {}

void WaveManager::update(float dt) {
  // If a wave is active but all enemies are defeated, prepare for next wave
  if (waveActive && environment->getEntityCount() == 0) {
    waveActive = false;
    waveTimer = 3.0f;  // cooldown between waves
    currentWave++;
  }
  // If wave not active, countdown timer until next wave
  else if (!waveActive) {
    waveTimer -= dt;
    if (waveTimer <= 0) {
      startNextWave();
    }
  }
  // If waveActive and enemies remain, do nothing (wave ongoing)
}

void WaveManager::startNextWave() {
  waveActive = true;

  // Calculate number of enemies based on wave number with exponential growth
  int baseCount = 5;
  float countScale = 1.2f;  // 20% increase per wave
  enemiesToSpawn = static_cast<int>(baseCount * std::pow(countScale, currentWave));

  // Base stats and scaling factors for enemy attributes
  float baseHP = 30.f;
  float hpScale = 1.15f;    // 15% HP increase per wave
  float baseDamage = 10.f;
  float dmgScale = 1.10f;   // 10% damage increase per wave
  float baseSpeed = 60.f;
  float speedScale = 1.05f; // 5% speed increase per wave

  for (int i = 0; i < enemiesToSpawn; ++i) {
    // Spawn position within environment boundaries
    int x = rand() % environment->getWidth();
    int y = rand() % environment->getHeight();

    // Boss spawn: every 10th wave, first enemy in the wave
    if (currentWave > 0 && currentWave % 10 == 0 && i == 0) {
      environment->spawnEntity(
          new GoblinLord(x, y,
                         baseHP * 3 * std::pow(hpScale, currentWave),
                         baseSpeed * 0.8 * std::pow(speedScale, currentWave),
                         baseDamage * 2 * std::pow(dmgScale, currentWave)));
    }
    // Goblin Brutes spawn every 5th enemy starting from wave 5
    else if (currentWave >= 5 && i % 5 == 0) {
      environment->spawnEntity(
          new GoblinBrute(x, y,
                          baseHP * 2 * std::pow(hpScale, currentWave),
                          baseSpeed * 0.9 * std::pow(speedScale, currentWave),
                          baseDamage * 1.5 * std::pow(dmgScale, currentWave)));
    }
    // Regular Goblins for other enemies
    else {
      environment->spawnEntity(
          new Goblin(x, y,
                     baseHP * std::pow(hpScale, currentWave),
                     baseSpeed * std::pow(speedScale, currentWave),
                     baseDamage * std::pow(dmgScale, currentWave)));
    }
  }
}

int WaveManager::getCurrentWave() const { return currentWave; }

bool WaveManager::isWaveActive() const { return waveActive; }