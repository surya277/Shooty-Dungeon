
// Engine Includes
#include "..\DragonFly Engine\GameManager.h"
#include "..\DragonFly Engine\LogManager.h"
#include "..\DragonFly Engine\ResourceManager.h"
#include "..\DragonFly Engine\WorldManager.h"
#include "..\DragonFly Engine\EventStep.h"

// Game Includes
#include "GameOver.h"
#include "GameStart.h"


GameOver::GameOver() {
	setType("GameOver");

	// set GameOver sprite
	if (setSprite("GameOver") == 0)
		time_to_live = getAnimation().getSprite()->getFrameCount() * 8;
	else
		time_to_live = 0;

	// set Location
	setLocation(df::CENTER_CENTER);

	// Play game over sound
	//df::Sound* over_sound = RM.getSound("game over");
	//over_sound->play();
}

// Override Draw to draw sprite
int GameOver::draw() {
	df::Object::draw();
	return 0;
}

// Handle event.
// Return 0 if ignored, else 1.
int GameOver::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	return 0;
}


// Count down to end of message.
void GameOver::step() {
	time_to_live--;
	if (time_to_live <= 0) {
		WM.markForDelete(this);
	}
}



GameOver::~GameOver() {
	WM.markForDelete(this);
	new GameStart;
}
