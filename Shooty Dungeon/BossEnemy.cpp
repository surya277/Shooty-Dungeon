

// Engine Includes
#include "../DragonFly Engine/WorldManager.h"
#include "../DragonFly Engine/DisplayManager.h"
#include "../DragonFly Engine/LogManager.h"
#include "../DragonFly Engine/EventStep.h"
#include "../DragonFly Engine/EventView.h"

// Game Includes
#include "BossEnemy.h"
#include "Points.h"
#include "Bullet.h"

BossEnemy::BossEnemy(int init_radius) {

	// Set Boss Enemy sprite;
	setSprite("Bot");

	// Set Object Type
	setType("BossEnemy");

	// Set Altitude of Enemy
	setAltitude(2);
	setPosition(df::Vector(50, 10));

	b_radius = init_radius;

	fire_slowdown = rand() % 70 + 80;
	fire_countdown = fire_slowdown;
	e_health = 100;
}

BossEnemy::~BossEnemy() {

	// Add points
	df::EventView ev(POINTS_STRING, 100, true);
	WM.onEvent(&ev);
}


// Event Handler
// Return 0 if ignored else 1
int BossEnemy::eventHandler(const df::Event* p_e) {
	// Move to player each step
	if (p_e->getType() == df::STEP_EVENT) {
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


// Called when collision occurs
void BossEnemy::hit(const df::EventCollision* p_collision_event) {
	// If Enemy on Enemy Collision Ignore
	if ((p_collision_event->getObject1()->getType() == "Enemy") &&
		(p_collision_event->getObject2()->getType() == "Enemy"))
		return;

	// If Player on Enemy Collision
	if (((p_collision_event->getObject1()->getType()) == "Player") ||
		((p_collision_event->getObject2()->getType()) == "Player")) {
		return;
	}


	// If bullet on Enemy Collision 
	if (p_collision_event->getObject1()->getType() == "PlayerBullet") {
		WM.markForDelete(p_collision_event->getObject1());
		reduceHealth();
	}
	else if (p_collision_event->getObject2()->getType() == "PlayerBullet") {
		WM.markForDelete(p_collision_event->getObject2());
		reduceHealth();
	}
}


// Handle step events
void BossEnemy::step() {
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;

	circleFire();
	

	//fire(direction);
}


void BossEnemy::circleFire() {
	// Check fire countdown
	if (fire_countdown > 0)
		return;
	fire_countdown = fire_slowdown;

	// Create Domain range (x axis)
	float d_start = this->getPosition().getX() - b_radius;
	float d_stop = this->getPosition().getX() + b_radius;

	float interval = fabs(d_stop - d_start) / 8;

	for (int i = 0; i <= 8; i++) {

		// Create Vector
		df::Vector temp_pos(0, 0);
		// Set Vector Position in circle around object
		temp_pos.setX(d_start + (i * interval));
		temp_pos.setY(sqrtf(powf(b_radius, 2) - powf(this->getPosition().getX() - temp_pos.getX(), 2)) + this->getPosition().getY());
		// Spawn bullet
		Bullet* b = new Bullet(temp_pos, "BossEnemy");
		// Set Bullet Direction
		df::Vector dir(0, 0);
		dir.setXY(temp_pos.getX() - this->getPosition().getX(), temp_pos.getY() - this->getPosition().getY());
		dir.normalize();
		b->setPosition(temp_pos);
		b->setDirection(dir);
		b->setSpeed(0.75f);

		// Repeat Process for 2nd Bullet
		temp_pos.setY(temp_pos.getY() + 2 * (this->getPosition().getY() - temp_pos.getY()));
		Bullet* b1 = new Bullet(temp_pos, "BossEnemy");
		dir.setXY(temp_pos.getX() - this->getPosition().getX(), temp_pos.getY() - this->getPosition().getY());
		dir.normalize();
		b1->setPosition(temp_pos);
		b1->setDirection(dir);
		b1->setSpeed(0.75f);

	}

}

// Reduce Boss Health
void BossEnemy::reduceHealth() {
	e_health = e_health - 5;

	if (e_health <= 0) {
		WM.markForDelete(this);
	}
}