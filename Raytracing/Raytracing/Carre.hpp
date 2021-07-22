#pragma once
#include "Object.hpp"

class Carre : virtual public Object
{
public:
	
	Carre();
	Carre(Color color);
	Carre(Material material);

	Ray getNormal(const Point& impact, const Point& observator);
	bool intersect(const Ray& ray, Point& impact, float& t0, float& t1);

private:

};