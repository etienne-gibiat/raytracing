#include "Matrix.hpp"

Matrix::Matrix() {
	for (int i = 0; i < m_rows * m_cols; ++i) {
		m_tab[i] = 0;
	}
	for (int i = 0; i < m_rows; ++i) {
		m_tab[i* m_rows + i] = 1;
	}
}

Matrix::Matrix(const Matrix& matrix) {
	for (int i = 0; i < m_rows; ++i) {
		for (int j = 0; j < m_cols; ++j) {
			m_tab[i * m_cols + j] = matrix.m_tab[i * m_cols + j];
		}
	}
}


float& Matrix::operator()(int i, int j) {
	return m_tab[i * m_cols + j];
}

Matrix& Matrix::inverse() {

    float inv[16], det;
    int i;

    inv[0] = m_tab[5] * m_tab[10] * m_tab[15] - m_tab[5] * m_tab[11] * m_tab[14] - m_tab[9] * m_tab[6] * m_tab[15] + m_tab[9] * m_tab[7] * m_tab[14] + m_tab[13] * m_tab[6] * m_tab[11] - m_tab[13] * m_tab[7] * m_tab[10];
    inv[4] = -m_tab[4] * m_tab[10] * m_tab[15] + m_tab[4] * m_tab[11] * m_tab[14] + m_tab[8] * m_tab[6] * m_tab[15] - m_tab[8] * m_tab[7] * m_tab[14] - m_tab[12] * m_tab[6] * m_tab[11] + m_tab[12] * m_tab[7] * m_tab[10];
    inv[8] = m_tab[4] * m_tab[9] * m_tab[15] - m_tab[4] * m_tab[11] * m_tab[13] - m_tab[8] * m_tab[5] * m_tab[15] + m_tab[8] * m_tab[7] * m_tab[13] + m_tab[12] * m_tab[5] * m_tab[11] - m_tab[12] * m_tab[7] * m_tab[9];
    inv[12] = -m_tab[4] * m_tab[9] * m_tab[14] + m_tab[4] * m_tab[10] * m_tab[13] + m_tab[8] * m_tab[5] * m_tab[14] - m_tab[8] * m_tab[6] * m_tab[13] - m_tab[12] * m_tab[5] * m_tab[10] + m_tab[12] * m_tab[6] * m_tab[9];
    inv[1] = -m_tab[1] * m_tab[10] * m_tab[15] + m_tab[1] * m_tab[11] * m_tab[14] + m_tab[9] * m_tab[2] * m_tab[15] - m_tab[9] * m_tab[3] * m_tab[14] - m_tab[13] * m_tab[2] * m_tab[11] + m_tab[13] * m_tab[3] * m_tab[10];
    inv[5] = m_tab[0] * m_tab[10] * m_tab[15] - m_tab[0] * m_tab[11] * m_tab[14] - m_tab[8] * m_tab[2] * m_tab[15] + m_tab[8] * m_tab[3] * m_tab[14] + m_tab[12] * m_tab[2] * m_tab[11] - m_tab[12] * m_tab[3] * m_tab[10];
    inv[9] = -m_tab[0] * m_tab[9] * m_tab[15] + m_tab[0] * m_tab[11] * m_tab[13] + m_tab[8] * m_tab[1] * m_tab[15] - m_tab[8] * m_tab[3] * m_tab[13] - m_tab[12] * m_tab[1] * m_tab[11] + m_tab[12] * m_tab[3] * m_tab[9];
    inv[13] = m_tab[0] * m_tab[9] * m_tab[14] - m_tab[0] * m_tab[10] * m_tab[13] - m_tab[8] * m_tab[1] * m_tab[14] + m_tab[8] * m_tab[2] * m_tab[13] + m_tab[12] * m_tab[1] * m_tab[10] - m_tab[12] * m_tab[2] * m_tab[9];
    inv[2] = m_tab[1] * m_tab[6] * m_tab[15] - m_tab[1] * m_tab[7] * m_tab[14] - m_tab[5] * m_tab[2] * m_tab[15] + m_tab[5] * m_tab[3] * m_tab[14] + m_tab[13] * m_tab[2] * m_tab[7] - m_tab[13] * m_tab[3] * m_tab[6];
    inv[6] = -m_tab[0] * m_tab[6] * m_tab[15] + m_tab[0] * m_tab[7] * m_tab[14] + m_tab[4] * m_tab[2] * m_tab[15] - m_tab[4] * m_tab[3] * m_tab[14] - m_tab[12] * m_tab[2] * m_tab[7] + m_tab[12] * m_tab[3] * m_tab[6];
    inv[10] = m_tab[0] * m_tab[5] * m_tab[15] - m_tab[0] * m_tab[7] * m_tab[13] - m_tab[4] * m_tab[1] * m_tab[15] + m_tab[4] * m_tab[3] * m_tab[13] + m_tab[12] * m_tab[1] * m_tab[7] - m_tab[12] * m_tab[3] * m_tab[5];
    inv[14] = -m_tab[0] * m_tab[5] * m_tab[14] + m_tab[0] * m_tab[6] * m_tab[13] + m_tab[4] * m_tab[1] * m_tab[14] - m_tab[4] * m_tab[2] * m_tab[13] - m_tab[12] * m_tab[1] * m_tab[6] + m_tab[12] * m_tab[2] * m_tab[5];
    inv[3] = -m_tab[1] * m_tab[6] * m_tab[11] + m_tab[1] * m_tab[7] * m_tab[10] + m_tab[5] * m_tab[2] * m_tab[11] - m_tab[5] * m_tab[3] * m_tab[10] - m_tab[9] * m_tab[2] * m_tab[7] + m_tab[9] * m_tab[3] * m_tab[6];
    inv[7] = m_tab[0] * m_tab[6] * m_tab[11] - m_tab[0] * m_tab[7] * m_tab[10] - m_tab[4] * m_tab[2] * m_tab[11] + m_tab[4] * m_tab[3] * m_tab[10] + m_tab[8] * m_tab[2] * m_tab[7] - m_tab[8] * m_tab[3] * m_tab[6];
    inv[11] = -m_tab[0] * m_tab[5] * m_tab[11] + m_tab[0] * m_tab[7] * m_tab[9] + m_tab[4] * m_tab[1] * m_tab[11] - m_tab[4] * m_tab[3] * m_tab[9] - m_tab[8] * m_tab[1] * m_tab[7] + m_tab[8] * m_tab[3] * m_tab[5];
    inv[15] = m_tab[0] * m_tab[5] * m_tab[10] - m_tab[0] * m_tab[6] * m_tab[9] - m_tab[4] * m_tab[1] * m_tab[10] + m_tab[4] * m_tab[2] * m_tab[9] + m_tab[8] * m_tab[1] * m_tab[6] - m_tab[8] * m_tab[2] * m_tab[5];

    det = m_tab[0] * inv[0] + m_tab[1] * inv[4] + m_tab[2] * inv[8] + m_tab[3] * inv[12];

    if (det == 0)
        return *this;

    det = 1.f / det;

    for (i = 0; i < 16; i++)
        m_tab[i] = inv[i] * det;

	return *this;
	//A modifier
}

Matrix& Matrix::operator*(const Matrix& m) {
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

Point& Matrix::operator*(const Point& p) {
	
	float x = this->m_tab[0] * p.tabPoint[0] + this->m_tab[1] * p.tabPoint[0] + this->m_tab[2] * p.tabPoint[0];
	float y = this->m_tab[4] * p.tabPoint[1] + this->m_tab[5] * p.tabPoint[1] + this->m_tab[6] * p.tabPoint[1];
	float z = this->m_tab[8] * p.tabPoint[2] + this->m_tab[9] * p.tabPoint[2] + this->m_tab[10] * p.tabPoint[2];
	Point res(x, y, z);

	return res;
}

Vector& Matrix::operator*( const Vector& v) {

	float x = this->m_tab[0] * v.tabVector[0] + this->m_tab[1] * v.tabVector[0] + this->m_tab[2] * v.tabVector[0];
	float y = this->m_tab[4] * v.tabVector[0] + this->m_tab[5] * v.tabVector[1] + this->m_tab[6] * v.tabVector[1];
	float z = this->m_tab[8] * v.tabVector[0] + this->m_tab[9] * v.tabVector[2] + this->m_tab[10] * v.tabVector[2];
	Vector res(x, y, z);

	return res;
}
