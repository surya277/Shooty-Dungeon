
// System Includes
#include <stdlib.h>	

// Engine Includes
#include "../DragonFly Engine/WorldManager.h"
#include "../DragonFly Engine/LogManager.h"
#include "../DragonFly Engine/EventStep.h"
#include "../DragonFly Engine/ObjectList.h"
#include "../DragonFly Engine/ObjectListIterator.h"

// Game Includes
#include "Enemy.h"
#include <time.h>



Enemy::Enemy() {

	// Set Enemy sprite
	setSprite("Enemy");
	
	// Set Object Type
	setType("Enemy");

	// Set Altitude of Enemy
	setAltitude(2);

	// PlaceHolder Velocity (TEST)
	setSpeed(0.5f);
	//setDirection(df::Vector(-1,0));

	spawnPoint();
}


Enemy::~Enemy(){

	// Add points
}


// Event Handler
// Return 0 if ignored else 1
int Enemy::eventHandler(const df::Event* p_e) {
	// Move to player each step
	if (p_e->getType() == df::STEP_EVENT) {
		moveToPlayer();
	}

	// Get collision event and reduce hp
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast<df::EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	// Out event (Just incase)
	return 0;
}


// Move to player location each step
void Enemy::moveToPlayer() {
	df::ObjectList playerList = WM.ObjectsOfType("Player");

	if (playerList.isEmpty()) {
		LM.writeLog("Player not found\n");
		return;
	}
	df::ObjectListIterator itr(&playerList);

	df::Vector player_pos = itr.currentObject()->getPosition();				// Get Player position
	df::Vector direction = player_pos - this->getPosition() ;				// Subtract enemy position from player position to get vector between both objects
	direction.normalize();													// Normalize to get direction vector

	//direction.setX(-direction.getX());	
	//direction.setY(-direction.getY());

	this->setDirection(direction);
}


// Called when collision occurs
void Enemy::hit(const df::EventCollision* p_collision_event) {
	// If Enemy on Enemy Collision Ignore
	if ((p_collision_event->getObject1()->getType() == "Enemy") &&
		(p_collision_event->getObject2()->getType() == "Enemy"))
		return;

	// If Player on Enemy Collision
	if (((p_collision_event->getObject1()->getType()) == "Player") ||
		((p_collision_event->getObject2()->getType()) == "Player")) {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());
	}


	// If bullet on Enemy Collision       
}



// Find Spawn point 
void Enemy::spawnPoint() {
	df::Vector start_pos;

	int world_horiz = (int)WM.getBoundary().getHorizontal();
	int world_vert = (int)WM.getBoundary().getVertical();
	srand(time(NULL));
	enum arr { UP, DOWN, LEFT, RIGHT };
	int random = rand() % 4;

	float horiz, vert;
	switch (random) {
	case UP:
		horiz = std::rand() % (world_horiz - 4) + 4.0f;
		vert = 0 - std::rand() % (world_vert + 3);
		break;

	case DOWN:
		horiz = std::rand() % (world_horiz - 4) + 4.0f;
		vert = world_vert + std::rand() % (world_vert + 3);
		break;

	case LEFT:
		horiz = 0 - std::rand() % (world_horiz - 4) + 4.0f;
		vert = std::rand() % (world_vert - 4) + 4;
		break;

	case RIGHT:
		horiz = world_horiz + std::rand() % (world_horiz + 4) + 4.0f;
		vert = std::rand() % (world_vert - 4) + 4.0f;
		break;

	}


	

	start_pos.setXY(horiz,vert);

	WM.moveObject(this, start_pos);
}



