#pragma once
#include "Object.hpp"

class Cube : virtual public Object
{
public:
	
	Cube();
	Cube(Color color, float cote);
	Cube(Material material, float cote);

	float cote;

	
	Ray getNormal(const Point& impact, const Point& observator);
	bool intersect(const Ray& ray, Point& impact, float& t0, float& t1);

private:

	float interSide(Ray& r, int dim, float offset);

};

