#pragma once
#include <math.h>
class Vector {
public:
    float* tabVector;
    Vector();
    Vector(int x,int y, int z);
    float norm();
    Vector normalized();
    float dot(Vector);
    friend Vector& operator+(Vector, Vector);
    friend Vector& operator-(Vector, Vector);
    friend Vector& operator*(Vector, float);
    friend Vector& operator/(Vector, float);
    Vector operator-();
    float operator[](int i);
};