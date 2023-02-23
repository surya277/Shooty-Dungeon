
// Engine Includes
#include "../DragonFly Engine/WorldManager.h"

// Game Includes
#include "Player.h"

// Constructor
Player::Player() {
	// Set Player sprite
	setSprite("Player");

	// Set Object type
	setType("Player");

	setAltitude(2);

	df::Vector start_pos(20, 20);
	WM.moveObject(this,start_pos);

}


// Destructor
Player::~Player() {

}


// Event Handler
// Return 0 if ignored else 1

int Player::eventHandler(const df::Event* p_e) {
	return 0;
}



