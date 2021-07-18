#include "Camera.hpp"

Camera::Camera() : Entity() {
	this->focal = 60;
	this->aspectratio = 1;
}

Camera::Camera(float focal, float aspectratio) : Entity() {
	this->focal = focal;
	this->aspectratio = aspectratio;
}

Ray Camera::getRay(float x, float y) {
	Ray r(-1 + 2 * x * aspectratio, -1 + 2 * y, 0, 0, 0, 0);
	Point foc(0, 0, focal);
	r.vector = (r.origin - foc);
	r = localToGlobal(r);
	Ray tmp = globalToLocal(r);
	r.normalized();
	return r;
}