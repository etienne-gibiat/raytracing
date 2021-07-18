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

	Point lp = globalToLocal(impact);
	Point lo = globalToLocal(observator);
	if ((lo - Point(0, 0, 0)).norm() < 1) {
		Vector lp2(lp[0], lp[1], lp[2]);
		Ray res = localToGlobal(Ray(lp, -lp2));
		res.normalized();
		return res;
	}
	Vector lp2(lp[0], lp[1], lp[2]);
	Ray res = localToGlobal(Ray(lp, lp2));
	res.normalized();
	return res;
}

bool Sphere::intersect(const Ray & ray, Point & impact, float& t0, float& t1){

		//Seulement le code ici fonctionne, à voir comment changer ca
		/*Point l = position - ray.origin;
		Vector tmp2 = ray.vector;
		Point tmp(tmp2[0], tmp2[1], tmp2[2]);
		float tca = l.dot(tmp);
		if (tca < 0) return false;
		float d2 = l.dot(l) - tca * tca;
		if (d2 > radius * radius) return false;
		float thc = sqrt((radius * radius) - d2);
		t0 = tca - thc;
		t1 = tca + thc;*/

	Ray r = globalToLocal(ray);
	r.normalized();
	float a = r.vector.dot(r.vector);
	float b = 2 * r.vector.dot(r.origin);
	float c = r.origin.dot(r.origin) - 1.0;
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
	t0 = t1 = t;
	return true;
}