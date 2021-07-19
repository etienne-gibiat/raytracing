#pragma once
#include "Object.hpp"

class CylindreInfini : virtual public Object
{
public:

	CylindreInfini();
	CylindreInfini(Color color);
	CylindreInfini(Material material);


	Ray getNormal(const Point& impact, const Point& observator);
	bool intersect(const Ray& ray, Point& impact, float& t0, float& t1);

};

