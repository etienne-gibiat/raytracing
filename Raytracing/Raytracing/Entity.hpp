#pragma once
#include "Matrix.hpp";
#include <math.h>;
#include"Ray.hpp";
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
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

	Point localToGlobal(const Point& p) const;
	Vector localToGlobal(const Vector& v) const;
	Ray localToGlobal(const Ray& r) const;

	Point globalToLocal(const Point& p) const;
	Vector globalToLocal(const Vector& v) const;
	Ray globalToLocal(const Ray& r) const;



};