
// Engine Includes
#include "..\DragonFly Engine\GameManager.h"
#include "..\DragonFly Engine\LogManager.h"
#include "..\DragonFly Engine\ResourceManager.h"
#include "..\DragonFly Engine\WorldManager.h"
#include "..\DragonFly Engine\DisplayManager.h"

// Game Includes
#include "GameStart.h"
#include "Player.h"
#include "Enemy.h"

GameStart::GameStart() {
	setType("GameStart");

	// set GameStart Sprite
	setSprite("GameStart");

	// Put Sprite in Screen Center
	setLocation(df::CENTER_CENTER);


	// Play start music.
	//start_music = RM.getMusic("start music");
	//playMusic();
}


void GameStart::start() {
	// Set View and Boundary
	//WM.setBoundary(df::Box(df::Vector(0, 0), DM.getHorizontal() * 2, DM.getVertical() * 2));
	//WM.setView(df::Box(df::Vector(0, 20), DM.getHorizontal(), DM.getVertical()));

	// Create Player
	Player* p1 = new Player;

	// Set View following


	// Spawn Enemies
	for (int i = 0; i < 5; i++) {
		new Enemy;
	}


	//start_music->pause();

	// Delete Game Start Object when done
	WM.markForDelete(this);
}


// Handle event.
// Return 0 if ignored, else 1.
int GameStart::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::KEYBOARD_EVENT) {
		df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*)p_e;
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			switch (p_keyboard_event->getKey()) {
			case df::Keyboard::P: 			// Play
				start();
				break;
			case df::Keyboard::Q:			// Quit
				GM.setGameOver();
				break;
			default:
				break;
			}
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Play start music.
void GameStart::playMusic() {
	start_music->play();
}

int GameStart::draw() {
	df::Object::draw();
	return 0;
}