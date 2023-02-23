
// Engine Includes
#include "..\DragonFly Engine\GameManager.h"
#include "..\DragonFly Engine\LogManager.h"
#include "..\DragonFly Engine\ResourceManager.h"

// Game Includes
#include "Enemy.h"


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
}


void populateWorld() {
	new Enemy;
}
