#pragma once
#include <math.h>
class Vector {
public:
    float* tabVector;
    Vector(int x,int y, int z);
    float norm();
    Vector normalized();
    float dot(Vector);
    friend Vector& operator+(Vector, Vector);
    friend Vector& operator-(Vector, Vector);
    friend Vector& operator*(Vector, float);
    friend Vector& operator/(Vector, float);
    float operator[](int i);
};