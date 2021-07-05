#include "Ray.hpp"


Ray::Ray(int ox, int oy, int oz, int vx, int vy, int vz) {
	origin = Point(ox, oy, oz);
	vector = Vector(vx, vy, vz);

}
Ray::Ray(Point p, Vector v) {
	origin = p;
	vector = v;

}