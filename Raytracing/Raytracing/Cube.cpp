#include "Cube.hpp"

Cube::Cube() : Object::Object()
{

}

Cube::Cube(Color color)
{
	this->material = Material(color, color, color, 0);

}

Cube::Cube(Material material)
{
	this->material = Material(material);

}

Ray Cube::getNormal(const Point& impact, const Point& observator) {

	Point lp = globalToLocal(impact);
	Point lo = globalToLocal(observator);
	Vector v(0, 0, 0);
	if (lp[0] > 0.999)v[0] = 1.0;
	else if (lp[0] < -0.999)v[0] = -1.0;
	else if (lp[1] > 0.999)v[1] = 1.0;
	else if (lp[1] < -0.999)v[1] = -1.0;
	else if (lp[2] > 0.999)v[2] = 1.0;
	else if (lp[2] < -0.999)v[2] = -1.0;
	if (lo[0]<1 && lo[0]>-1 && lo[1]<1 && lo[1]>-1 && lo[2]<1 && lo[2]>-1) {
		Ray res = localToGlobal(Ray(lp, -v));
		res.normalized();
		return res;
	}
	Ray res = localToGlobal(Ray(lp, v));
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