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
	float z = 1;
	if (lo[2] < 0)z = -1;
	Ray res =  localToGlobal(Ray(lp, Vector(0, 0, z)));
	res.normalized();
	return res;
}

bool Plan::intersect(const Ray& ray, Point& impact, float& t0, float& t1) {

	Ray lr = globalToLocal(ray);
	lr.normalized();
	if (lr.vector[2]<0.0001 && lr.vector[2]>-0.0001)return false;
	if (lr.vector[2] * lr.origin[2] > 0)return false;
	float t = -lr.origin[2] / lr.vector[2];
	Vector p = lr.origin + t * lr.vector;
	Point p2(p[0], p[1], p[2]);		 	      	   	  
	impact = localToGlobal(p2);
	t0 = t1 = t;
	return true;

	/*float t;
	float dv;
	dv = normale.dot(ray.vector);
	if (dv == 0)
		return false;
	t = ((-(normale.dot(ray.origin - position))) / dv);
	if (t < 0)
		return false;
	Vector tmp = ray.origin + ray.vector * t;
	//tmp.normalized();
	impact = Point(tmp[0], tmp[1], tmp[2]);
	t0 = t;
	t1 = t;

	return true;*/
}