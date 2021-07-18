#pragma once
#include "Object.hpp"

class Triangle : virtual public Object
{
public:

	Triangle();
	Triangle(Color color, Vector v1, Vector v2);
	Triangle(Material material, Vector v1, Vector v2);

	Vector v0, v1, v2;


	Ray getNormal(const Point& impact, const Point& observator);
	bool intersect(const Ray& ray, Point& impact, float& t0, float& t1);

};
