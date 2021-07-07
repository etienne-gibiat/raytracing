#pragma once
#include "Object.hpp"

class Sphere : virtual public Object
{
public:

	Sphere();
	Sphere(Color color, Point position, float radius);
	Sphere(Material material, Point position, float radius);

	Point position;
	float radius;

	Ray getNormal(const Point& impact, const Point& observator);
	bool intersect(const Ray& ray, Point& impact);


};



