
#include "Object.h";

namespace df {

	class BulletPattern : public Object {
	private:
		float radius;

	public:
		BulletPattern(float init_radius);

		void setRadius(float new_radius);

		float getRadius();

		float* getPoints();

	};
}