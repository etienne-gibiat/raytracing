#include "Vector.hpp"




Vector::Vector() {
	tabVector[0] = 0;
	tabVector[1] = 0;
	tabVector[2] = 0;
}


Vector::Vector(float x, float y, float z) {
	tabVector[0] = x;
	tabVector[1] = y;
	tabVector[2] = z;


}

float& Vector::operator[](int i) {
	return tabVector[i];
}


float Vector::dot(Vector v) {
	float res = tabVector[0] * v[0] + tabVector[1] * v[1] + tabVector[2] * v[2];
	return res;
}

float Vector::dot(Point p) {
	float res = tabVector[0] * p[0] + tabVector[1] * p[1] + tabVector[2] * p[2];
	return res;
}

float Vector::norm() {
	float norme = pow(tabVector[0],2) + pow(tabVector[1], 2) + pow(tabVector[2], 2);
	norme = (float)sqrt(norme);
	return norme;
}
float Vector::length2() const { return tabVector[0] * tabVector[0] + tabVector[1] * tabVector[1] + tabVector[2] * tabVector[2]; }
Vector& Vector::normalized() {
	float nor2 = length2();
	if (nor2 > 0) {
		float invNor = 1 / sqrt(nor2);
		
		tabVector[0] *= invNor, tabVector[1] *= invNor, tabVector[2] *= invNor;
	}
	return *this;

}


Vector& operator+(Vector v, Vector v2) {
	float x = v[0] + v2[0];
	float y = v[1] + v2[1];
	float z = v[2] + v2[2];
	Vector res(x,y,z);
	return res;
}

Vector& operator+(Point p, Vector v2) {
	float x = p[0] + v2[0];
	float y = p[1] + v2[1];
	float z = p[2] + v2[2];
	Vector res(x, y, z);
	return res;
}

Vector& operator-(Vector v, Vector v2) {
	float x = v[0] - v2[0];
	float y = v[1] - v2[1];
	float z = v[2] - v2[2];
	Vector res(x, y, z);
	return res;
}
Vector& operator*(Vector v, float f) {
	float x = v[0] * f;
	float y = v[1] * f;
	float z = v[2] * f;
	Vector res(x, y, z);
	return res;

}

Vector& operator*(float f, Vector v) {
	float x = v[0] * f;
	float y = v[1] * f;
	float z = v[2] * f;
	Vector res(x, y, z);
	return res;
}

Vector& operator/(Vector v, float f) {

	float x = v[0] / f;
	float y = v[1] / f;
	float z = v[2] / f;
	Vector res(x, y, z);
	return res;
}

Vector Vector::operator-() {
	return Vector(-tabVector[0], -tabVector[1], -tabVector[2]);
	
}

Vector Vector::operator=(Vector v) {
	tabVector[0] = v.tabVector[0];
	tabVector[1] = v.tabVector[1];
	tabVector[2] = v.tabVector[2];
	return *this;
}

Vector Vector::operator=(Point p) {
	tabVector[0] = p.tabPoint[0];
	tabVector[1] = p.tabPoint[1];
	tabVector[2] = p.tabPoint[2];
	return *this;
}
