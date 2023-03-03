// Engine includes
#include "../DragonFly Engine/WorldManager.h"
#include "../DragonFly Engine/ResourceManager.h"
#include "../DragonFly Engine/LogManager.h"
#include "../DragonFly Engine/EventStep.h"
#include "../DragonFly Engine/EventView.h"

// Game includes
#include "EnemyWaveManager.h"
#include "Enemy.h"
#include "BossEnemy.h"
#include "GameOver.h"

EnemyWaveManager::EnemyWaveManager()
{
	wave_count = 0;
	enemy_per_wave = 5;
	enemy_count = 0;

	wave_music = RM.getMusic("WaveMusic");
	boss_music = RM.getMusic("BossMusic");
}

EnemyWaveManager& EnemyWaveManager::getInstance()
{
	static EnemyWaveManager waveManager;
	return waveManager;
}

int EnemyWaveManager::startUp()
{
	wave_music->play(true);

	return 0;
}

int EnemyWaveManager::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT) {
		if (enemy_count < 1) spawnEnemies();
		if (wave_count == 3 && enemy_count < 1) new GameOver;
	}
	
	return 0;
}

void EnemyWaveManager::spawnEnemies()
{
	if (wave_count < 3) {
		wave_count += 1;
		LM.writeLog("DEBUG: Spawn Enemy Wave\n");
		LM.writeLog("DEBUG: Wave count: %d\n", wave_count);

		for (int i = 0; i < enemy_per_wave; i++) {
			new Enemy;
			enemy_count++;
		}

		if (wave_count == 3) {
			BossEnemy* boss = new BossEnemy(4);
			enemy_count++;
			wave_music->pause();
			boss_music->play(true);
		}

		enemy_per_wave += 2;
	}
}

void EnemyWaveManager::modifyEnemyCount(int count)
{
	if (enemy_count > 0) {
		enemy_count = enemy_count + count;
	}
	
}

int EnemyWaveManager::getEnemyCount() const
{
	return enemy_count;
}
