#include "WaveManager.h"

#include <cmath>
#include <cstdlib>

WaveManager::WaveManager(Environment* env)
    : environment(env),
      currentWave(0),
      waveTimer(3.0f),
      waveActive(false),
      enemiesToSpawn(0) {}

void WaveManager::update(float dt) {
  // If wave is active and all enemies are gone, start timer for next wave
  if (waveActive && environment->getEntityCount() == 0) {
    waveActive = false;
    waveTimer = 3.0f;  // 3 seconds between waves
    currentWave++;
  } else if (!waveActive) {
    waveTimer -= dt;
    if (waveTimer <= 0) {
      startNextWave();
    }
  }
  // If waveActive, do nothing (enemies are already spawned)
}

void WaveManager::startNextWave() {
  waveActive = true;
  int baseCount = 5;
  float countScale = 1.2f;  // 20% more enemies per wave
  enemiesToSpawn =
      static_cast<int>(baseCount * std::pow(countScale, currentWave));

  float baseHP = 30.f;
  float hpScale = 1.15f;  // 15% more HP per wave
  float baseDamage = 10.f;
  float dmgScale = 1.10f;  // 10% more damage per wave
  float baseSpeed = 60.f;
  float speedScale = 1.05f;  // 5% more speed per wave

  for (int i = 0; i < enemiesToSpawn; ++i) {
    int x = rand() % environment->getWidth();
    int y = rand() % environment->getHeight();

    // Boss every 10th wave, first enemy in wave
    if (currentWave > 0 && currentWave % 10 == 0 && i == 0) {
      environment->spawnEntity(
          new GoblinLord(x, y, baseHP * 3 * std::pow(hpScale, currentWave),
                         baseSpeed * 0.8 * std::pow(speedScale, currentWave),
                         baseDamage * 2 * std::pow(dmgScale, currentWave)));
    }
    // Brutes every 5th enemy after wave 5
    else if (currentWave >= 5 && i % 5 == 0) {
      environment->spawnEntity(
          new GoblinBrute(x, y, baseHP * 2 * std::pow(hpScale, currentWave),
                          baseSpeed * 0.9 * std::pow(speedScale, currentWave),
                          baseDamage * 1.5 * std::pow(dmgScale, currentWave)));
    }
    // Regular goblins
    else {
      environment->spawnEntity(
          new Goblin(x, y, baseHP * std::pow(hpScale, currentWave),
                     baseSpeed * std::pow(speedScale, currentWave),
                     baseDamage * std::pow(dmgScale, currentWave)));
    }
  }
}

int WaveManager::getCurrentWave() const { return currentWave; }

bool WaveManager::isWaveActive() const { return waveActive; }
