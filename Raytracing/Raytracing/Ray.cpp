#include "Ray.hpp"


Ray::Ray()
{
	origin = Point();
	vector = Vector();
}

Ray::Ray(float ox, float oy, float oz, float vx, float vy, float vz) {
	origin = Point(ox, oy, oz);
	vector = Vector(vx, vy, vz);

}
Ray::Ray(Point p, Vector v) {
	origin = p;
	vector = v;

}

void Ray::normalized() {
	this->vector = this->vector.normalized();
}