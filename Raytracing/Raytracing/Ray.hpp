#pragma once
#include <math.h>
#include "Point.hpp"
#include "Vector.hpp"
class Ray {
public:

	Point origin;
	Vector vector;

	Ray(int, int, int, int, int, int);
	Ray(Point, Vector);




};