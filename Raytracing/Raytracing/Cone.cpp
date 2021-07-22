#include "Cone.hpp"
#include <math.h> 
#define INFINITY 1e8

Cone::Cone() : Object::Object()
{

}

Cone::Cone(Color color)
{
	this->material = Material(color, color, color, 0);

}

Cone::Cone(Material material)
{
	this->material = Material(material);

}

Point Cone::getTextureCoordinates(const Point& p) {
	
	return Point(0, 0, 0);
}

Ray Cone::getNormal(const Point& impact, const Point& observator) {



    Point lp = globalToLocal(impact);
    Point lo = globalToLocal(observator);

    float x = lp[0] * (INFINITY / 0.523599);
    float y = 0.523599 / INFINITY;
    float z = lp[2] * (INFINITY / 0.523599);
    //Ray res(lp, Vector(lp[0], lp[1], sin(0.523599)));
    /*Vector v = Vector(0, -1, 0);
    Vector cp = Vector(lp[0], lp[1], lp[3]);
    Vector n = cp * v.dot(cp) / cp.dot(cp) - v;*/

    Ray res(lp, Vector(x, y, z));
    //Ray res(lp, n);

    res = localToGlobal(res);
    res.normalized();
    return res;

}

bool Cone::intersect(const Ray& ray, Point& impact, float& t0, float& t1) {
    
    Ray r = globalToLocal(ray);
    r.normalized();

    Point o = r.origin;

    Vector dir = r.vector;
    Vector v = Vector(0, -1, 0);
    Vector co = Vector(o[0], o[1], o[2]);

    float coss = pow(cos(0.523599), 2); 

    float a = pow(dir.dot(v), 2) - coss;
    float b = 2 * (dir.dot(v) * co.dot(v) - dir.dot(co) * coss);
    float c = pow(co.dot(v), 2) - co.dot(co) * coss;

    float delta = b * b - 4 * (a * c);
    if (delta < 0) return false;


    delta = sqrt(delta);
    t0 = (-b - delta) / (2. * a);
    t1 = (-b + delta) / (2. * a);

    float t = t0;
    if (t < 0. || t1 > 0. && t1 < t) t = t1;
    if (t < 0.) return false;

    Vector cp = o + t * dir;
    float h = cp.dot(v);
    if (h < 0.) return false;

    //Vector n = cp * v.dot(cp) / cp.dot(cp) - v;
    //Point p(n[0], n[1], n[2]);
    Point p(cp[0], cp[1], cp[2]);
    impact = localToGlobal(p);
    t0 = t;
    t1 = t;


    return true;
}