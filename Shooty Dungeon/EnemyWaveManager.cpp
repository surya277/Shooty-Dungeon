// Engine includes
#include "../DragonFly Engine/WorldManager.h"
#include "../DragonFly Engine/ResourceManager.h"
#include "../DragonFly Engine/LogManager.h"
#include "../DragonFly Engine/EventStep.h"
#include "../DragonFly Engine/EventView.h"
#include "../DragonFly Engine/ObjectList.h"
#include "../DragonFly Engine/ObjectListIterator.h"

// Game includes
#include "EnemyWaveManager.h"
#include "Enemy.h"
#include "BossEnemy.h"
#include "GameOver.h"

EnemyWaveManager::EnemyWaveManager()
{
	setType("WaveManager");

	wave_count = 0;
	enemy_per_wave = 5;
	enemy_count = 0;

	wave_music = RM.getMusic("WaveMusic");
	boss_music = RM.getMusic("BossMusic");

	player_health = 0;
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
		if (enemy_count < 1 && player_health > 0 && wave_count < 3) spawnEnemies();
		if (wave_count == 3 && enemy_count < 1) clearObjects();
	}
	
	return 0;
}

void EnemyWaveManager::spawnEnemies()
{

	if (wave_count < 3) {
		wave_count += 1;
		
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

void EnemyWaveManager::clearObjects()
{
	df::ObjectList object_list = WM.getAllObjects();
	df::ObjectListIterator i(&object_list);
	for (i.first(); !i.isDone(); i.next())
	{
		df::Object* p_object = i.currentObject();
		if (p_object->getType() == "Player" || p_object->getType() == "Enemy" || p_object->getType() == "BossEnemy" || p_object->getType() == "ViewObject" || p_object->getType() == "PlayerBullet" || p_object->getType() == "EnemyBullet" || p_object->getType() == "BossBullet") WM.markForDelete(p_object);
	}
	
	wave_music->pause();
	boss_music->pause();
}

void EnemyWaveManager::updatePlayerHealth(int health)
{
	player_health = health;
}
