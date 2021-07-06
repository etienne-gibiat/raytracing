#pragma once
#include "Object.hpp"

class Sphere : public Object
{
public:

	Sphere();
	Sphere(Color color);
	Ray getNormal(const Point& impact, const Point& observator);
	bool intersect(const Ray& ray, Point& impact);


};



