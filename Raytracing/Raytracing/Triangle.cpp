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

    /*Point lp = globalToLocal(impact);
    Point lo = globalToLocal(observator);
    float z = 1;
    if (lo[z] < 0)z = -1;
    Ray res = localToGlobal(Ray(lp, Vector(0, 0, z)));
    res.normalized();

 
    return res;*/
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

bool Triangle::intersect(const Ray& ray, Point& impact, float& t0, float& t1) {

        Ray r = globalToLocal(ray);
        const float EPSILON = 0.0000001;
        Vector vertex0 = this->v0;
        Vector vertex1 = this->v1;
        Vector vertex2 = this->v2;
        Vector edge1, edge2, h, s, q;
        float a, f, u, v;
        edge1 = vertex1 - vertex0;
        edge2 = vertex2 - vertex0;
        h = r.vector.cross(edge2);
        a = edge1.dot(h);
        if (a > -EPSILON && a < EPSILON)
            return false;    // Le rayon est parallèle au triangle.

        f = 1.0 / a;
        Vector tmp(r.origin[0], r.origin[1], r.origin[2]);
        s = tmp - vertex0;
        u = f * (s.dot(h));
        if (u < 0.0 || u > 1.0)
            return false;
        q = s.cross(edge1);
        v = f * r.vector.dot(q);
        if (v < 0.0 || u + v > 1.0)
            return false;

        // On calcule t pour savoir ou le point d'intersection se situe sur la ligne.
        float t = f * edge2.dot(q);
        if (t > EPSILON) // Intersection avec le rayon
        {
            Vector p = r.origin + r.vector * t;
            p = localToGlobal(p);
            impact[0] = p[0];
            impact[1] = p[1];
            impact[2] = p[2];

            t0 = t;
            t1 = t;

            return true;
        }
        else // On a bien une intersection de droite, mais pas de rayon.
            return false;
        
        //return true; // this ray hits the triangle 

}