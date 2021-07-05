#pragma once
#include <math.h>

class Point {
public:
    float* tabPoint;
    Point();
    Point(int x, int y, int z);
    float dot(Point);
    friend Point& operator+(Point, Point);
    friend Point& operator-(Point, Point);
    friend Point& operator*(Point, float);
    friend Point& operator/(Point, float);
    float operator[](int i);
    Point operator-();


};