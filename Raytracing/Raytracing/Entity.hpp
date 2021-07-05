#pragma once
#include "Matrix.hpp";
#include <math.h>;
class Entity {
public:
	Matrix trans;
	Matrix transInv;
	void translate(float x, float y, float z);
	void scale(float);
	void rotateX(float);
	void rotateY(float);
	void rotateZ(float);



};