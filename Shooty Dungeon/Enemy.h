#pragma once

#include "..\DragonFly Engine\Object.h"
#include "..\DragonFly Engine\EventCollision.h"

class Enemy	: public df::Object
{
private:
	int e_health;							// Enemy health
	int fire_slowdown;						// Fire Slowdown
	int fire_countdown;						// Fire Countdown

	void hit(const df::EventCollision* p_collision_event);

	void spawnPoint();

public:
	// Constructor
	Enemy();		

	// Destructor
	~Enemy();


	// Event Handler
	// Return 0 if ignored else 1
	int eventHandler(const df::Event* p_e);
};

