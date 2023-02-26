#pragma once

#include "..\DragonFly Engine\Object.h"
#include "..\DragonFly Engine\EventCollision.h"
#include "..\DragonFly Engine\EventKeyboard.h"
#include "..\DragonFly Engine\EventMouse.h"

// Forward declarations
class Reticle;

class Player : public df::Object
{
	

private:
	int p_health;						// Player Health
	int fire_slowdown;					// Fire Slowdown
	int fire_countdown;					// Fire Countdown
	Reticle* p_reticle;

	void hit(const df::EventCollision* p_collision_event);

public:
	// Constructor
	Player();

	// Destructor
	~Player();

	// Event Handler
	// Return 0 if ignored else 1
	int eventHandler(const df::Event* p_e);

	void kbd(const df::EventKeyboard* p_keyboard_event);

	void move(int dx, int dy);

	void mouse(const df::EventMouse* p_mouse_event);

	void fire(df::Vector mouse_position);
};

