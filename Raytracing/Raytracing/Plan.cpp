#include "Plan.hpp"

Plan::Plan() : Object::Object()
{

}

Plan::Plan(Color color)
{
	this->material = Material(color, color, color, 0);

}

Plan::Plan(Material material)
{
	this->material = Material(material);
}

Ray Plan::getNormal(const Point& impact, const Point& observator) {

	Point lp = globalToLocal(impact);
	Point lo = globalToLocal(observator);
	float z = 1;
	if (lo[1] < 0)z = -1;
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
	t0 = t;
	t1 = t;

	return true;
}

Point Plan::getTextureCoordinates(const Point& p)
{
	Point lp = globalToLocal(p);
	float x = lp[0] - (int)lp[0];
	float y = lp[1] - (int)lp[1];
	if (x < 0)x += 1;
	if (y < 0)y += 1;

	return Point(x, y, 0);
}
