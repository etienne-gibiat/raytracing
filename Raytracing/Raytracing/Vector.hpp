#pragma once
#include <math.h>


class Point {
public:
    float tabPoint[3];
    Point();
    Point(float x, float y, float z);
    float dot(Point);
    friend Point& operator+(Point, Point);
    //friend Point& operator+(Point, Vector);
    friend Point& operator-(Point, Point);
    friend Point& operator*(Point, float);
    friend Point& operator/(Point, float);
    //Point& operator=(Vector);
    float& operator[](int i);
    float norm();


};

class Vector {
public:
    float tabVector[3];
    Vector();
    Vector(float x,float y, float z);
    float norm();
    Vector& normalized();
    float dot(Vector);
    float dot(Point);
    friend Vector& operator+(Vector, Vector);
    friend Vector& operator+(Point, Vector);
    friend Vector& operator-(Vector, Vector);
    friend Vector& operator*(Vector, float);
    friend Vector& operator*(float, Vector);
    friend Vector& operator/(Vector, float);
    float length2() const;
    Vector operator=(Vector);
    Vector operator=(Point);
    Vector operator-();
    float& operator[](int i);
};

