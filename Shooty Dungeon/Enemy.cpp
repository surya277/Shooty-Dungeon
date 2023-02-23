
// Engine Includes
#include "../DragonFly Engine/WorldManager.h"
#include "../DragonFly Engine/LogManager.h"
#include "../DragonFly Engine/EventStep.h"
#include "../DragonFly Engine/ObjectList.h"
#include "../DragonFly Engine/ObjectListIterator.h"

// Game Includes
#include "Enemy.h"



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
	if (p_e->getType() == df::STEP_EVENT) {
		moveToPlayer();
	}
	return 0;
}


// Move to player location
void Enemy::moveToPlayer() {
	df::ObjectList playerList = WM.ObjectsOfType("Player");

	if (playerList.isEmpty()) {
		LM.writeLog("Player not found\n");
		return;
	}
	df::ObjectListIterator itr(&playerList);

	df::Vector player_pos = itr.currentObject()->getPosition();
	df::Vector direction = this->getPosition() - player_pos;
	direction.normalize();
	direction.setX(-direction.getX());
	direction.setY(-direction.getY());
	this->setDirection(direction);
	//WM.moveObject(this,player_pos);
}


// Called when collision occurs
void Enemy::hit(const df::EventCollision* p_collision_event) {

}



// Find Spawn point 
void Enemy::spawnPoint() {
	df::Vector start_pos;

	int world_horiz = (int) WM.getBoundary().getHorizontal();
	int world_vert = (int)WM.getBoundary().getVertical();

	start_pos.setXY(world_horiz, world_vert- 10);

	WM.moveObject(this, start_pos);
}



