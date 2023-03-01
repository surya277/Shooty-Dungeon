
// System Includes
#include <stdlib.h>	
#include <time.h>

// Engine Includes
#include "../DragonFly Engine/WorldManager.h"
#include "../DragonFly Engine/LogManager.h"
#include "../DragonFly Engine/EventStep.h"
#include "../DragonFly Engine/EventView.h"
#include "../DragonFly Engine/ObjectList.h"
#include "../DragonFly Engine/ObjectListIterator.h"

// Game Includes
#include "Enemy.h"
#include "Bullet.h"
#include "Points.h"



Enemy::Enemy() {

	// Set Enemy sprite
	setSprite("Bot");
	
	// Set Object Type
	setType("Enemy");

	// Set Altitude of Enemy
	setAltitude(2);

	// PlaceHolder Velocity (TEST)
	setSpeed(0.25f);
	//setDirection(df::Vector(-1,0));

	
	fire_slowdown = rand() % 40 + 80;
	fire_countdown = fire_slowdown;
	
	spawnPoint();
}


Enemy::~Enemy(){

	// Add points
	df::EventView ev(POINTS_STRING, 10, true);
	WM.onEvent(&ev);
}


// Event Handler
// Return 0 if ignored else 1
int Enemy::eventHandler(const df::Event* p_e) {
	// Move to player each step
	if (p_e->getType() == df::STEP_EVENT) {
		moveToPlayer();
		step();
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


// Handle step events

void Enemy::step() {
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;
	

	df::ObjectList playerList = WM.ObjectsOfType("Player");

	if (playerList.isEmpty()) {
		LM.writeLog("Player not found\n");
		return;
	}
	df::ObjectListIterator itr(&playerList);

	df::Vector player_pos = itr.currentObject()->getPosition();				// Get Player position
	df::Vector direction = player_pos - this->getPosition();				// Subtract enemy position from player position to get vector between both objects
	direction.normalize();

	fire(direction);
}


// Fire Bullet towards Player
void Enemy::fire(df::Vector target) {
	if (fire_countdown > 0)
		return;
	fire_countdown = fire_slowdown;
	Bullet* p = new Bullet(getPosition(), getType());

	p->setDirection(target);
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

	if (getPosition().getDistance(player_pos) < 15.f) {
		setSpeed(0.f);
	}
	else {
		setSpeed(0.25f);
	}
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
	if (((p_collision_event->getObject1()->getType()) == "Bullet") ||
		((p_collision_event->getObject2()->getType()) == "Bullet")) {
		//WM.markForDelete(p_collision_event->getObject1());
		//WM.markForDelete(p_collision_event->getObject2());
	}
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


	
	LM.writeLog("horz and vert : %d %d \n", horiz, vert);
	start_pos.setXY(horiz,vert);

	df::ObjectList collision_list = WM.getCollision(this, start_pos);
	while (!collision_list.isEmpty()) {
		start_pos.setX(start_pos.getX() + 3);											// Doesn't Always Work (May cause them to appear in screen)
		start_pos.setY(start_pos.getY() + 3);
		collision_list = WM.getCollision(this, start_pos);
	}

	WM.moveObject(this, start_pos);
}



