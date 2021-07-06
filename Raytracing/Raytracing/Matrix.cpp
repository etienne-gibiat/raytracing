#include "Matrix.hpp"

Matrix::Matrix() {
	m_tab = new float[m_cols * m_rows];
	for (int i = 0; i < m_cols; ++i) {
		m_tab[i * m_cols + i] = 1;
	}
}

Matrix::Matrix(const Matrix& matrix) {
	m_tab = new float[m_cols * m_rows];
	for (int i = 0; i < m_cols; ++i) {
		m_tab[i * m_cols + i] = matrix.m_tab[i * m_cols + i];
	}
}


float& Matrix::operator()(int i, int j) {
	return m_tab[i * m_cols + j];
}

Matrix Matrix::inverse() {
	return *this;
	//A modifier
}

Matrix Matrix::operator*(Matrix m) {
	// a tester
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            for (int inner = 0; inner < 3; inner++) {
               m_tab[row * m_cols + col] = m_tab[row * m_cols + col] * m.m_tab[inner * m_cols + col];	
            }
        }
    }

	return *this;
}

Point& Matrix::operator*(Point p) {
	
	float x = this->m_tab[0] * p[0] + this->m_tab[1] * p[0] + this->m_tab[2] * p[0];
	float y = this->m_tab[4] * p[0] + this->m_tab[5] * p[1] + this->m_tab[6] * p[1];
	float z = this->m_tab[8] * p[0] + this->m_tab[9] * p[2] + this->m_tab[10] * p[2];
	Point res(x, y, z);

	return res;
}

Vector& Matrix::operator*( Vector v) {

	float x = this->m_tab[0] * v[0] + this->m_tab[1] * v[0] + this->m_tab[2] * v[0];
	float y = this->m_tab[4] * v[0] + this->m_tab[5] * v[1] + this->m_tab[6] * v[1];
	float z = this->m_tab[8] * v[0] + this->m_tab[9] * v[2] + this->m_tab[10] * v[2];
	Vector res(x, y, z);

	return res;
}
