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
	Ray(int, int, int, int, int, int);
	Ray(Point, Vector);

	void normalized();




};