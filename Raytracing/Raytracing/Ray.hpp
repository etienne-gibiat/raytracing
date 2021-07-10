#pragma once
#include <math.h>
#include "Point.hpp"
#pragma once
#include "Vector.hpp"

class Ray {
public:

	Point origin;
	Vector vector;

	Ray();
	Ray(float, float, float, float, float, float);
	Ray(Point, Vector);

	void normalized();




};