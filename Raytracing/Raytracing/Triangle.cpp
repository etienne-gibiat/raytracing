#include "Triangle.hpp"

Triangle::Triangle() : Object::Object()
{
	this->v0 = Vector(-1, -1, 0);
	this->v1 = Vector(-1, 1, 0);
	this->v2 = Vector(1, -1, 0);
}

Triangle::Triangle(Color color, Vector v1, Vector v2)
{
	this->material = Material(color, color, color, 0, 0, 0);
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

        double x1 = v1[0] - v0[0];
        double y1 = v1[1] - v0[1];
        double z1 = v1[2] - v0[2];
        double x2 = v2[0] - v0[0];
        double y2 = v2[1] - v0[1];
        double z2 = v2[2] - v0[2];

        double x3 = r.vector[0];
        double y3 = r.vector[1];
        double z3 = r.vector[2];
        double xp = r.origin[0];
        double yp = r.origin[1];
        double zp = r.origin[2];

        double dx = xp - v0[0];
        double dy = yp - v0[1];
        double dz = zp - v0[2];

        double D =
            z1 * y3 * x2 - y1 * z3 * x2 - x3 * z1 * y2 - y3 * x1 * z2 + z3 * x1 * y2 +
            x3 * y1 * z2;
        double u =
            (-y3 * dx * z2 + y3 * x2 * dz - x2 * z3 * dy + dx * z3 * y2 -
                x3 * y2 * dz + x3 * dy * z2) / D;
        double v =
            (x3 * y1 * dz + z3 * x1 * dy - y1 * z3 * dx - x3 * z1 * dy -
                y3 * x1 * dz + z1 * y3 * dx) / D;
        double t =
            (dx * z1 * y2 - dx * y1 * z2 - x1 * y2 * dz + x1 * dy * z2 +
                x2 * y1 * dz - x2 * z1 * dy) / D;

        if (fabs(D) > EPSILON && u > EPSILON && v > EPSILON
            && (u + v) <= 1 + EPSILON)
        {

            impact[0] = r.origin[0] + r.vector[0] * t;
            impact[1] = r.origin[1] + r.vector[1] * t;
            impact[2] = r.origin[2] + r.vector[2] * t;


            impact = localToGlobal(impact);

            return true;
        }
        else
            return false;

}