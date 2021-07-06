#include "Light.hpp"

Light::Light() : Entity()
{
	id = Color();
	is = Color();
}

Ray Light::getRayToLight(Point& p) {
	Vector dir(trans(0, 3), trans(1, 3), trans(2, 3));
	return Ray(p, dir);
}
/*Ray Light::getRayFromLight(const Point& p)const {

}
Vector Light::getVectorToLight(const Point& p)const {

}
Vector Light::getVectorFromLight(const Point& p)const {

}*/