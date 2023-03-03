
// Engine Includes
#include "../DragonFly Engine/WorldManager.h"
#include "../DragonFly Engine/LogManager.h"

// Game Includes
#include "Player.h"
#include "Reticle.h"
#include "Bullet.h"
#include "GameOver.h"
#include "EventDamage.h"

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

	health = 5;

	p_health_view = new df::ViewObject;
	p_health_view->setLocation(df::TOP_LEFT);
	p_health_view->setViewString("Health");
	p_health_view->setColor(df::YELLOW);
	p_health_view->setValue(health);
}


// Destructor
Player::~Player() {
	// Call GameOver Screen
	new GameOver;

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

	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast<const df::EventMouse*> (p_e);
		mouse(p_mouse_event);
	}
	
	if (p_e->getType() == DAMAGE_EVENT) {
		health--;
		// Update health view object
		p_health_view->setValue(health);
	}

	return 0;
}

void Player::kbd(const df::EventKeyboard* p_keyboard_event) {
	switch (p_keyboard_event->getKey()) {
		case df::Keyboard::Q: // Quit game
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) WM.markForDelete(this);
			break;

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


// Handle Mouse Events;

void Player::mouse(const df::EventMouse* p_mouse_event) {
	if ((p_mouse_event->getMouseAction() == df::CLICKED) && (p_mouse_event->getMouseButton() == df::Mouse::LEFT)) {
		fire(p_mouse_event->getMousePosition());
	}
}

// Fire bullets towards clicked position

void Player::fire(df::Vector mouse_position) {
	if (fire_countdown > 0)
		return;

	fire_countdown = fire_slowdown;

	Bullet* bullet = new Bullet(getPosition(), getType());
	df::Vector direction;
	direction = mouse_position - getPosition();
	direction.normalize();
	bullet->setDirection(direction);
}


