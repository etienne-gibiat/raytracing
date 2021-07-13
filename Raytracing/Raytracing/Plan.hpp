#pragma once
#include "Object.hpp"

class Plan : virtual public Object
{
public:
	Vector normale;
	Plan();
	Plan(Color color, Point position);
	Plan(Material material, Point position);

	Ray getNormal(const Point& impact, const Point& observator);
	bool intersect(const Ray& ray, Point& impact, float& t0, float& t1);


};