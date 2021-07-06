#include "Vector.hpp"


Point::Point() {
	tabPoint = new float[3];
	tabPoint[0] = 0;
	tabPoint[1] = 0;
	tabPoint[2] = 0;
}
Point::Point(int x, int y, int z) {
	tabPoint = new float[3];
	tabPoint[0] = x;
	tabPoint[1] = y;
	tabPoint[2] = z;


}

float Point::operator[](int i) {
	return tabPoint[i];

}


float Point::dot(Point v) {
	float res = tabPoint[0] * v[0] + tabPoint[1] * v[1] + tabPoint[2] * v[2];
	return res;
}


Point& operator+(Point v, Point v2) {
	float x = v[0] + v2[0];
	float y = v[1] + v2[1];
	float z = v[2] + v2[2];
	Point res(x, y, z);
	return res;
}

/*Point& operator+(Point v, Vector v2) {
	float x = v[0] + v2[0];
	float y = v[1] + v2[1];
	float z = v[2] + v2[2];
	Point res(x, y, z);
	return res;
}*/


Point& operator-(Point v, Point v2) {
	float x = v[0] - v2[0];
	float y = v[1] - v2[1];
	float z = v[2] - v2[2];
	Point res(x, y, z);
	return res;
}

/*Point& Point::operator=(Vector v) {
	float x = v[0];
	float y = v[1];
	float z = v[2];
	Point res(x, y, z);
	return res;
}*/

Point& operator*(Point v, float f) {
	float x = v[0] * f;
	float y = v[1] * f;
	float z = v[2] * f;
	Point res(x, y, z);
	return res;

}
Point& operator/(Point v, float f) {

	float x = v[0] / f;
	float y = v[1] / f;
	float z = v[2] / f;
	Point res(x, y, z);
	return res;
}

Point Point::operator-() {
	return Point(-tabPoint[0], -tabPoint[1], -tabPoint[2]);
}
