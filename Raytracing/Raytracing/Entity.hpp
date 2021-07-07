#pragma once
#include "Matrix.hpp";
#include <math.h>;
#include"Ray.hpp";

class Entity {
public:

	Entity();
	Entity(Matrix trans);

	Matrix trans;
	Matrix transInv;

	void translate(float x, float y, float z);
	void scale(float);
	void rotateX(float);
	void rotateY(float);
	void rotateZ(float);

	Point localToGlobal(const Point& p);
	Vector localToGlobal(const Vector& v);
	Ray localToGlobal(const Ray& r);

	Point globalToLocal(Point p);
	Vector globalToLocal(Vector v);
	Ray globalToLocal(Ray r);



};