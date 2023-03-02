
#include "Object.h";

namespace df {
	
	const int MAX_BULLET_POINTS = 20;

	class BulletPattern : public Object {
	private:
		float radius;

	public:
		BulletPattern(float init_radius);

		void setRadius(float new_radius);

		float getRadius();

		Vector* getPoints(Vector pos, int num_points);

	};
}