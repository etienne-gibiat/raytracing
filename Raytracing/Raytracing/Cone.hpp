#pragma once
#include "Object.hpp"

class Cone : virtual public Object
{
public:

	Cone();
	Cone(Color color);
	Cone(Material material);

	Point getTextureCoordinates(const Point& p);


	Ray getNormal(const Point& impact, const Point& observator);
	bool intersect(const Ray& ray, Point& impact, float& t0, float& t1);

private:

};

