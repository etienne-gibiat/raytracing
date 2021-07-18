#include "Triangle.hpp"

Triangle::Triangle() : Object::Object()
{
	this->v0 = Vector(-1, -1, 0);
	this->v1 = Vector(-1, 1, 0);
	this->v2 = Vector(1, -1, 0);
}

Triangle::Triangle(Color color, Vector v1, Vector v2)
{
	this->material = Material(color, color, color, 0);
	this->v0 = Vector(-1, -1, 0);
	this->v1 = Vector(-1, 1, 0);
	this->v2 = Vector(1, -1, 0);

}

Triangle::Triangle(Material material, Vector v1, Vector v2)
{
	this->material = Material(material);
	this->v0 = Vector(-1, -1, 0);
	this->v1 = Vector(-1, 1, 0);
	this->v2 = Vector(1, -1, 0);

}

Ray Triangle::getNormal(const Point& impact, const Point& observator) {

    Point lp = globalToLocal(impact);
    Point lo = globalToLocal(observator);
    float y = 1;
    if (lo[1] < 0)y = -1;
    Ray res = localToGlobal(Ray(lp, Vector(0, y, 0)));
    res.normalized();

 
    return res;
}

bool Triangle::intersect(const Ray& ray, Point& impact, float& t0, float& t1) {

        Ray r = globalToLocal(ray);
        // compute plane's normal
        Vector v0v1 = v1 - v0;
        Vector v0v2 = v2 - v0;
        // no need to normalize
        Vector N = v0v1.cross(v0v2); // N 
        float area2 = N.length2();

        // Step 1: finding P

        // check if ray and plane are parallel ?
        float NdotRayDirection = N.dot(r.vector);
        if (fabs(NdotRayDirection) < 0.00000000000000000000001) // almost 0 
            return false; // they are parallel so they don't intersect ! 

        // compute d parameter using equation 2
        float d = N.dot(v0);

        // compute t (equation 3)
        float t = (N.dot(r.origin) + d) / NdotRayDirection;
        // check if the triangle is in behind the ray
        if (t < 0) return false; // the triangle is behind 

        // compute the intersection point using equation 1
        Vector P = r.origin + t * r.vector;

        // Step 2: inside-outside test
        Vector C; // vector perpendicular to triangle's plane 

        // edge 0
        Vector edge0 = v1 - v0;
        Vector vp0 = P - v0;
        C = edge0.cross(vp0);
        if (N.dot(C) < 0) return false; // P is on the right side 

        // edge 1
        Vector edge1 = v2 - v1;
        Vector vp1 = P - v1;
        C = edge1.cross(vp1);
        if (N.dot(C) < 0)  return false; // P is on the right side 

        // edge 2
        Vector edge2 = v0 - v2;
        Vector vp2 = P - v2;
        C = edge2.cross(vp2);
        if (N.dot(C) < 0) return false; // P is on the right side; 

        Vector p = localToGlobal(P);
        impact[0] = p[0];
        impact[1] = p[1];
        impact[2] = p[2];

        t0 = t1 = t;
        return true; // this ray hits the triangle 

}