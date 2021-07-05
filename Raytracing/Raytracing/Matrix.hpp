#pragma once


class Matrix {
public:
	int m_rows = 4;
	int m_cols = 4;
	float* m_tab;
	Matrix();
	float& operator()(int i, int j);
	Matrix inverse();
	Matrix operator*(Matrix);

};