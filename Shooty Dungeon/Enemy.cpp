
// Engine Includes
#include "../DragonFly Engine/WorldManager.h"

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
	setVelocity(df::Vector(-0.25, 0));

	spawnPoint();
}


Enemy::~Enemy(){

	// Add points
}


// Event Handler
// Return 0 if ignored else 1
int Enemy::eventHandler(const df::Event* p_e) {
	return 0;
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



