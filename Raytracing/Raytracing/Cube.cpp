#include "Cube.hpp"

Cube::Cube() : Object::Object()
{
	this->position = Point(0, 0, 0);
	this->cote = 1;
}

Cube::Cube(Color color, float cote)
{
	this->material = Material(color, color, color, 0);
	this->position = Point(position);
	this->cote = cote;
}

Cube::Cube(Material material, float cote)
{
	this->material = Material(material);
	this->position = Point(position);
	this->cote = cote;
}

Ray Cube::getNormal(const Point& impact, const Point& observator) {

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

float Cube::interSide(Ray& r, int dim, float offset) {
	float t = -1;
	if (r.vector[dim]<0.00001 && r.vector[dim]>-0.00001)return -1;
	t = (offset - r.origin[dim]) / r.vector[dim];
	if (t < 0)return -1;
	for (int d = 0; d < 3; d++) {
		if (d == dim)continue;
		float x = r.origin[d] + t * r.vector[d];
		if (x < -1 || x > 1)return -1;
	}
	return t;
}

bool Cube::intersect(const Ray& ray, Point& impact, float& t0, float& t1) {

	Ray r = globalToLocal(ray);
	r.normalized();

	float mint = -1;
	float offsets[] = { -1,1 };
	
	for (int d = 0; d < 3; d++) {
		for (int o = 0; o < 2; o++) {
			float t = interSide(r, d, offsets[o]);
			if (t >= 0 && (mint<0 || mint>t)) {
				mint = t;
			}
		}
	}

	if (mint >= 0) {
		Vector p = localToGlobal(r.origin + mint * r.vector);
		impact[0] = p[0];
		impact[1] = p[1];
		impact[2] = p[2];
		t0 = t1 = mint;
		return true;
	}

	return false;
}