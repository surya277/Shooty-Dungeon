#pragma once

// Engine Includes
#include "../DragonFly Engine/Object.h"
#include "../DragonFly Engine/EventCollision.h"

class Bullet : public df::Object
{

private:
	std::string owner;						// Owner of the bullet

	void out();													// Handle out of bounds event
	void hit(const df::EventCollision* p_collision_event);

public:
	Bullet(df::Vector spawn_pos, std::string object_type);	// , std::string bullet_type);

	int eventHandler(const df::Event* p_e);
};

