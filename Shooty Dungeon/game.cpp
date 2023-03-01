
// Engine Includes
#include "..\DragonFly Engine\GameManager.h"
#include "..\DragonFly Engine\LogManager.h"
#include "..\DragonFly Engine\ResourceManager.h"
#include "..\DragonFly Engine\WorldManager.h"				//(Added for Enemy Testing)

// Game Includes
#include "GameStart.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"


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
	RM.loadSprite("sprites/saucer-spr.txt", "Enemy");
	RM.loadSprite("sprites/ship-spr.txt", "Player");
	RM.loadSprite("sprites/bullet-spr.txt", "Bullet");
	RM.loadSprite("sprites/spiderbot-spr.txt", "Bot");
	RM.loadSprite("sprites/gamestart-spr.txt", "GameStart");
	//RM.loadSprite("sprites/gamestartshoot-spr.txt", "GameStart");
	RM.loadSprite("sprites/gameover-spr.txt", "GameOver");
}


void populateWorld() {
	LM.writeLog("Populating World\n");

	new GameStart();
	/*
	for (int i = 0; i < 5;i++)
		new Enemy;

	Enemy* e = new Enemy();
	e->setPosition(df::Vector(40, 5));
	new Player;
	*/
	//new Bullet(df::Vector(10, WM.getBoundary().getVertical() - 7));
}
