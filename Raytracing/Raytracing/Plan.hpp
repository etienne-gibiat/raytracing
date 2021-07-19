#pragma once
#include "Object.hpp"

class Plan : virtual public Object
{
public:
	Vector normale;
	Plan();
	Plan(Color color);
	Plan(Material material);

	Ray getNormal(const Point& impact, const Point& observator);
	bool intersect(const Ray& ray, Point& impact, float& t0, float& t1);
	Point getTextureCoordinates(const Point& p);


};