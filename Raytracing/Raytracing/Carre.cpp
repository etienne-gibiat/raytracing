#include "Carre.hpp"

Carre::Carre() : Object::Object()
{

}

Carre::Carre(Color color)
{

	this->material = Material(color, color, color, 0);

}

Carre::Carre(Material material)
{

	this->material = Material(material);

}

Ray Carre::getNormal(const Point& impact, const Point& observator) {

	Point p = globalToLocal(impact);

	Vector v(0, 0, 0);

	if (globalToLocal(observator)[2] > 0) {

		v[2] = 1;

	}
	else {

		v[2] = -1;

	}

	Ray r(p, v);

	return localToGlobal(r);
}

bool Carre::intersect(const Ray& ray, Point& impact, float& t0, float& t1) {

	Ray r = globalToLocal(ray);
	r.normalized();
	
	if (r.vector[2]<0.0001 && r.vector[2]>-0.0001)return false;
	if (r.vector[2] * r.origin[2] > 0)return false;
	float t = -r.origin[2] / r.vector[2];
	Vector n = r.origin + t * r.vector;
	Point p(n[0], n[1], n[2]);
	if (p[0] < -1 || p[0]>1 || p[1] < -1 || p[1]>1)return false;
	impact = localToGlobal(p);
	return true;

	Vector v = r.origin + t * r.vector;
	p = Point(v[0], v[1], v[2]);
	impact = localToGlobal(p);
	t0 = t;
	t1 = t;
	return true;
}