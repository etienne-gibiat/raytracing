#pragma once
#include <math.h>


class Point {
public:
    float* tabPoint;
    Point();
    Point(int x, int y, int z);
    float dot(Point);
    friend Point& operator+(Point, Point);
    //friend Point& operator+(Point, Vector);
    friend Point& operator-(Point, Point);
    friend Point& operator*(Point, float);
    friend Point& operator/(Point, float);
    //Point& operator=(Vector);
    float operator[](int i);
    Point operator-();


};

class Vector {
public:
    float* tabVector;
    Vector();
    Vector(int x,int y, int z);
    float norm();
    Vector normalized();
    float dot(Vector);
    float dot(Point);
    friend Vector& operator+(Vector, Vector);
    friend Vector& operator+(Point, Vector);
    friend Vector& operator-(Vector, Vector);
    friend Vector& operator*(Vector, float);
    friend Vector& operator*(float, Vector);
    friend Vector& operator/(Vector, float);
    Vector operator=(Vector);
    Vector operator=(Point);
    Vector operator-();
    float& operator[](int i);
};

