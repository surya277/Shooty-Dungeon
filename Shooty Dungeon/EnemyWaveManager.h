#pragma once

#include "../DragonFly Engine/Object.h"
#include "../DragonFly Engine/Music.h"

#define EWM EnemyWaveManager::getInstance()

class EnemyWaveManager : public df::Object {
private:
	EnemyWaveManager();										// Private (Singleton)
	EnemyWaveManager(EnemyWaveManager const&);					// Don't allow copy
	void operator=(EnemyWaveManager const&);

	int wave_count; // current wave count
	int enemy_per_wave; // No. of enemies to spawn per wave
	int enemy_count; // No. of enemies in the world
	df::Music* wave_music;
	df::Music* boss_music;

public:
	static EnemyWaveManager& getInstance();

	int startUp();

	int eventHandler(const df::Event* p_e);

	void spawnEnemies();

	void modifyEnemyCount(int count);

	int getEnemyCount() const;
};