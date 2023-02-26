

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

	float* BulletPattern::getPoints() {
		float i = 1;
		return &i;
	}
}