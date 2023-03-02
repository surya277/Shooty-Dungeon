
// Engine Includes
#include "WorldManager.h"
#include "BulletPattern.h"

namespace df {

	BulletPattern::BulletPattern(float init_radius) {
		radius = init_radius;
	}

	void BulletPattern::setRadius(float new_radius) {
		radius = new_radius;
	}

	float BulletPattern::getRadius() {
		return radius;
	}

	Vector* BulletPattern::getPoints(Vector pos, int num_points) {
		float d_start = pos.getX() - radius;
		float d_stop = pos.getX() + radius;

		float interval =  fabs(d_stop - d_start) / num_points;

		Vector* coords[MAX_BULLET_POINTS];
		for (int i = 0; i < num_points; i++) {
			Vector* temp_pos = new Vector(0, 0);
			temp_pos->setX(d_start + (i * interval));
			temp_pos->setY(sqrtf(powf(radius, 2) - powf(pos.getX() - temp_pos->getX(), 2)) - pos.getY());
			coords[i] = temp_pos;
			//coords[i]->setX(d_start + (i * interval));
			//coords[i]->setY(sqrtf(powf(radius, 2) - powf(pos.getX() - coords[i]->getX(), 2)) - pos.getY());
		}
		return *coords;
	}
}