
// Engine Includes
#include "../DragonFly Engine/LogManager.h"
#include "../DragonFly Engine/EventOut.h"
#include "../DragonFly Engine/WorldManager.h"
#include "../DragonFly Engine/ObjectList.h"
#include "../DragonFly Engine/ObjectListIterator.h"
#include "../DragonFly Engine/Vector.h"


// Game Includes
#include "Bullet.h"
#include "Reticle.h"
#include "Player.h"
#include "Enemy.h"
#include "EventDamage.h"


// Can make bullet class common for both Player and enemy
// Have to change Bullet type, sprite, velocity, spawn position based on if player bullet or enemy bullet


Bullet::Bullet(df::Vector spawn_pos,std::string object_type) {
	
	owner = object_type;

	if (owner == "Player")
	{
		// set Bullet sprite
		setSprite("Bullet");
		// Set Bullet Type
		setType("PlayerBullet");
	}
	else if (owner == "Enemy")
	{
		// set Bullet sprite
		setSprite("EnemyBullet");
		// Set Bullet Type
		setType("EnemyBullet");
	}
	else if (owner == "BossEnemy")
	{
		// set Bullet sprite
		setSprite("BossBullet");
		// Set Bullet Type
		setType("BossBullet");
	}

	setSolidness(df::SOFT);

	// Set Bullet Velocity
	setVelocity(df::Vector(1, 0)); // Move 1 space right every game loop.

	spawnPos(spawn_pos);

}


// Set Spawn position of Bullet
void Bullet::spawnPos(df::Vector spawn_pos) {
	// Set starting location, based on object position
	df::Vector p(spawn_pos.getX() + 7, spawn_pos.getY());
	if (owner == "Player")
	{
		df::ObjectList li = WM.ObjectsOfType("Reticle");
		df::ObjectListIterator itr(&li);
		df::Vector vReticle = itr.currentObject()->getPosition();

		if ((spawn_pos.getX() > vReticle.getX()) && (owner == "Player"))
			p.setX(spawn_pos.getX() - 7);
	}
	setPosition(p);
}

// Handle Events
// Return 0 if ignored, else 1.

int Bullet::eventHandler(const df::Event* p_e) {
	// Check if Out of bounds event
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	// Check if collision event
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast<const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}


	// Ignored
	return 0;
}


// Handle out of bounds
void Bullet::out() {
	WM.markForDelete(this);
}


// Handle Collision
void Bullet::hit(const df::EventCollision* p_collision_event) {
	if (((p_collision_event->getObject1()->getType() == "Enemy" || p_collision_event->getObject2()->getType() == "Enemy")) && (owner == "Player")) {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());
	}

	else if (((p_collision_event->getObject1()->getType() == "Player" || p_collision_event->getObject2()->getType() == "Player")) && ((owner == "Enemy") || (owner == "BossEnemy"))) {
		WM.markForDelete(this);
		EventDamage ed;
		WM.onEvent(&ed);
	}
}
