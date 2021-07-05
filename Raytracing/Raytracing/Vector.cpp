#include "Vector.hpp"




Vector::Vector() {
	tabVector = new float[3];
	tabVector[0] = 0;
	tabVector[1] = 0;
	tabVector[2] = 0;
}


Vector::Vector(int x, int y, int z) {
	tabVector = new float[3];
	tabVector[0] = x;
	tabVector[1] = y;
	tabVector[2] = z;


}

float Vector::operator[](int i) {
	return tabVector[i];

}


float Vector::dot(Vector v) {
	float res = tabVector[0] * v[0] + tabVector[1] * v[1] + tabVector[2] * v[2];
	return res;
}
float Vector::norm() {
	float norme = pow(tabVector[0],2) + pow(tabVector[1], 2) + pow(tabVector[2], 2);
	norme = sqrt(norme);
	return norme;
}

Vector Vector::normalized() {
	float vectorNorm = norm();
	Vector res(tabVector[0] / vectorNorm, tabVector[1] / vectorNorm, tabVector[2] / vectorNorm);
	return res;

}


Vector& operator+(Vector v, Vector v2) {
	float x = v[0] + v2[0];
	float y = v[1] + v2[1];
	float z = v[2] + v2[2];
	Vector res(x,y,z);
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
