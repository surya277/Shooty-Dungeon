
// Engine Includes
#include "..\DragonFly Engine\GameManager.h"
#include "..\DragonFly Engine\LogManager.h"
#include "..\DragonFly Engine\ResourceManager.h"
#include "..\DragonFly Engine\WorldManager.h"				//(Added for Enemy Testing)
#include "..\DragonFly Engine\BulletPattern.h"

// Game Includes
#include "GameStart.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "BossEnemy.h"


void loadResources();
void populateWorld();

int main(int argc, char* argv[]) {
	// Start Game Manager
	GM.startUp();

	// Set flush to enable continuous logging
	LM.setFlush(true);

	// Load Game Resources using Resource Manager
	loadResources();

	// Populate Game world with objects
	populateWorld();

	// Run game
	GM.run();

	// Shut Down Game Manager
	GM.shutDown();

}


// Load Resources such as sprites, Audio
void loadResources() {
	//RM.loadSprite("sprites/saucer-spr.txt", "Enemy");
	RM.loadSprite("sprites/player-spr.txt", "Player");
	RM.loadSprite("sprites/bullet-spr.txt", "Bullet");
	RM.loadSprite("sprites/spiderbot-spr.txt", "Bot");
	RM.loadSprite("sprites/cocoonbot-spr.txt", "BossBot");
	RM.loadSprite("sprites/gamestart-spr.txt", "GameStart");
	//RM.loadSprite("sprites/gamestartshoot-spr.txt", "GameStart1");
	//RM.loadSprite("sprites/gamestartshoot2-spr.txt", "GameStart");
	RM.loadSprite("sprites/gameover-spr.txt", "GameOver");
	RM.loadSprite("sprites/bossbullet-spr.txt", "BossBullet");
	RM.loadSprite("sprites/enemy-bullet-spr.txt", "EnemyBullet");

	RM.loadMusic("audio/title-music.wav", "TitleMusic");
	RM.loadMusic("audio/wave-music.wav", "WaveMusic");
	RM.loadMusic("audio/boss-music.wav", "BossMusic");
}


void populateWorld() {
	new GameStart();
}
