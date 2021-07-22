#include "CylindreInfini.hpp"

CylindreInfini::CylindreInfini() : Object::Object()
{
	this->position = Point(0, 0, 0);
}

CylindreInfini::CylindreInfini(Color color)
{
	this->material = Material(color, color, color, 0);
	this->position = Point(position);
}

CylindreInfini::CylindreInfini(Material material)
{
	this->material = Material(material);
	this->position = Point(position);
}

Ray CylindreInfini::getNormal(const Point& impact, const Point& observator) {

	Point lp = globalToLocal(impact);
	Point lo = globalToLocal(observator);
	if ((lo - Point(0, lo[1], 0)).norm() > 1) {
		Ray res(lp, Vector(lp[0], 0, lp[2]));
		res = localToGlobal(res);
		res.normalized();
		return res;
	}
	Ray res(lp, Vector(-lp[0], 0, -lp[2]));
	res = localToGlobal(res);
	res.normalized();
	return res;

}

bool CylindreInfini::intersect(const Ray& ray, Point& impact, float& t0, float& t1) {
	Ray r = globalToLocal(ray);
	r.normalized();

	float a = r.vector[0] * r.vector[0] + r.vector[2] * r.vector[2];
	float b = 2 * (r.vector[0] * r.origin[0] + r.vector[2] * r.origin[2]);
	float c = r.origin[0] * r.origin[0] + r.origin[2] * r.origin[2] - 1.0;
	float delta = b * b - 4 * a * c;

	if (delta < 0)return false;

	float t;
	if (delta < 0.0001) {
		t = -b / (2 * a);
	}
	else {
		t = (-b - sqrt(delta)) / (2 * a);
		if (t < 0)t = (-b + sqrt(delta)) / (2 * a);
	}
	if (t < 0)return false;

	Vector p = r.origin + t * r.vector;
	Point p2(p[0], p[1], p[2]);
	impact = localToGlobal(p2);
	t0 = t;
	t1 = t;
	return true;
	}