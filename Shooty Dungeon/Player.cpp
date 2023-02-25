
// Engine Includes
#include "../DragonFly Engine/WorldManager.h"

// Game Includes
#include "Player.h"
#include "Reticle.h"

// Constructor
Player::Player() {
	// Set Player sprite
	setSprite("Player");

	// Set Object type
	setType("Player");

	setAltitude(2);

	df::Vector start_pos(20, 20);
	WM.moveObject(this,start_pos);

	// Create reticle object and draw the aiming reticle
	p_reticle = new Reticle();
	p_reticle->draw();
}


// Destructor
Player::~Player() {
	// Destroy reticle object instance
	WM.markForDelete(p_reticle);
}


// Event Handler
// Return 0 if ignored else 1

int Player::eventHandler(const df::Event* p_e) {
	// Handle keyboard events
	if (p_e->getType() == df::KEYBOARD_EVENT)
	{
		const df::EventKeyboard* p_keyboard_event = dynamic_cast<const df::EventKeyboard*>(p_e);
		kbd(p_keyboard_event);
		return 1;
	}

	return 0;
}

void Player::kbd(const df::EventKeyboard* p_keyboard_event) {
	switch (p_keyboard_event->getKey()) {
		//case df::Keyboard::Q: // Quit game
		//	if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) WM.markForDelete(this);
		//	break;

		case df::Keyboard::W: // Move up
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) move(0, -1);
			break;

		case df::Keyboard::A: // Move Left
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) move(-1, 0);
			break;

		case df::Keyboard::S: // Move down
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) move(0, 1);
			break;

		case df::Keyboard::D: // Move right
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) move(1, 0);
			break;
	}
}

void Player::move(int dx, int dy) {
	df::Vector new_pos(getPosition().getX() + dx, getPosition().getY() + dy);

	// Check object screen bounds and move
	if ((new_pos.getY() > 3) && (new_pos.getY() < WM.getBoundary().getVertical())) WM.moveObject(this, new_pos);
}



