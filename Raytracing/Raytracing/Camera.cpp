#include "Camera.hpp"

Camera::Camera() : Entity() {
	this->focal = 60;
}

Camera::Camera(float focal) : Entity() {
	this->focal = focal;
}

Ray Camera::getRay(float x, float y) {
    Point p(x * 2 - 1, y * 2 - 1, 0.);
    Vector v(0, 0, 0);
    Ray r(p, v);
    Point foc(0, 0, focal);
    r.vector = (r.origin - foc);
    r = localToGlobal(r);
    r.normalized();
    return r;
}