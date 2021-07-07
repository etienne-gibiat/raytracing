#include "Sphere.hpp"

Sphere::Sphere() : Object::Object()
{
	this->position = Point(0, 0, 0);
	this->radius = 1;
}

Sphere::Sphere(Color color, Point position, float radius)
{
	this->material = Material(color, color, color, 0);
	this->position = Point(position);
	this->radius = radius;
}

Sphere::Sphere(Material material, Point position, float radius)
{
	this->material = Material(material);
	this->position = Point(position);
	this->radius = radius;
}

Ray Sphere::getNormal(const Point& impact, const Point& observator) {

	Point p = globalToLocal(impact);

	Vector v(0, 0, 0);

	Point o = globalToLocal(observator);
	if ((o[0] >= 1 || o[0] <= -1) || (o[1] >= 1 || o[1] <= -1) || (o[2] >= 1 || o[2] <= -1)) {

		v[0] = p[0];
		v[1] = p[1];
		v[2] = p[2];

	}
	else {

		v[0] = -p[0];
		v[1] = -p[1];
		v[2] = -p[2];

	}

	Ray r(impact, localToGlobal(v));

	r.normalized();
	return r;
}

bool Sphere::intersect(const Ray & ray, Point & impact){


	Ray r = globalToLocal(ray);
	r.normalized();
	float a = r.vector.dot(r.vector);
	float b = 2 * r.vector.dot(r.origin);
	float c = r.origin.dot(r.origin) - radius * radius;
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

	Vector v = r.origin + t * r.vector;
	Point p(v[0], v[1], v[2]);
	impact = localToGlobal(p);
	return true;
}