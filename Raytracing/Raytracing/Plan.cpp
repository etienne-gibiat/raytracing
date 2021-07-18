#include "Plan.hpp"

Plan::Plan() : Object::Object()
{
	this->position = Point(0, 0, 0);
}

Plan::Plan(Color color, Point position)
{
	this->material = Material(color, color, color, 0);
	this->position = Point(position);
}

Plan::Plan(Material material, Point position)
{
	this->material = Material(material);
	this->position = Point(position);
}

Ray Plan::getNormal(const Point& impact, const Point& observator) {

	Point lp = globalToLocal(impact);
	Point lo = globalToLocal(observator);
	float y = 1;
	if (lo[1] < 0)y = -1;
	Ray res =  localToGlobal(Ray(lp, Vector(0, y, 0)));
	res.normalized();
	return res;
}

bool Plan::intersect(const Ray& ray, Point& impact, float& t0, float& t1) {

	Ray lr = globalToLocal(ray);
	lr.normalized();
	if (lr.vector[1]<0.0001 && lr.vector[1]>-0.0001)return false;
	if (lr.vector[1] * lr.origin[1] > 0)return false;
	float t = -lr.origin[1] / lr.vector[1];
	Vector p = lr.origin + t * lr.vector;
	Point p2(p[0], p[1], p[2]);		 	      	   	  
	impact = localToGlobal(p2);
	t0 = t1 = t;

	return true;
}