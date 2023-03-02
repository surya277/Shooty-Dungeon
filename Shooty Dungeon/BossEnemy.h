#pragma once

#include "..\DragonFly Engine\Object.h"
#include "..\DragonFly Engine\EventCollision.h"

class BossEnemy : public df::Object
{
private:
	int e_health;		// Boss Enemy Health
	int b_radius;			// Bullet spawn radius
	int fire_slowdown;	// Fire Slowdown
	int fire_countdown;	// Fire Countdown

	void hit(const df::EventCollision* p_collision_event);

	void step();

	void circleFire();

	void reduceHealth();

public:
	// Constructor
	BossEnemy(int init_radius);

	// Destructor
	~BossEnemy();


	// Event Handler
	// Return 0 if ignored else 1
	int eventHandler(const df::Event* p_e);
};

