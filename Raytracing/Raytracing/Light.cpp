#include "Light.hpp"

Light::Light() : Entity()
{
	id = Color();
	is = Color();
}

Ray Light::getRayToLight(Point& p) {
	Point ptLight(trans(0, 3), trans(1, 3), trans(2, 3));
	Vector dir(ptLight[0] - p[0], ptLight[1] - p[1], ptLight[2] - p[2]);
	dir.normalized();
	return Ray(p, dir);
}
Ray Light::getRayFromLight(Point& p){
	Point ptLight(transInv(0, 3), transInv(1, 3), transInv(2, 3));
	Vector dir(p[0] - ptLight[0], p[1] - ptLight[1], p[2] - ptLight[2]);
	return Ray(p, dir);
}
/*
Vector Light::getVectorToLight(const Point& p)const {

}
Vector Light::getVectorFromLight(const Point& p)const {

}*/