#include "Matrix.hpp"

Matrix::Matrix() {
	m_tab = new float[m_cols * m_rows];
	for (int i = 0; i < m_cols; ++i) {
		m_tab[i * m_cols + i] = 1;
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
}
