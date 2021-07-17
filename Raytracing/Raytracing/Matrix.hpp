#pragma once
#include "Vector.hpp"


class Matrix {
public:
	int m_rows = 4;
	int m_cols = 4;
	float m_tab[16];
	Matrix();
	Matrix(const Matrix& matrix);
	float& operator()(int i, int j);
	Point& operator*(const Point&) const;
	Vector& operator*(const Vector&) const;
	Matrix& inverse();
	Matrix& operator*(Matrix&);

};