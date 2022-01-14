//
// Created by ploca14 on 03.12.21.
//

#include "matrix.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cassert>

int Matrix::index(int row, int col) const {
    assert(row < m_rows && col < m_cols);
    return m_cols * row + col;
}

int &Matrix::operator()(int row, int col) {
    return m_data[index(row, col)];
}

int Matrix::operator()(int row, int col) const {
    return m_data[index(row, col)];
}

Matrix::Matrix(int rows, int cols):
        m_rows(rows),
        m_cols(cols),
        m_data(new int[rows * cols])
{

    std::fill_n(m_data.get(), rows*cols, 0);
}

std::ostream &operator<<(std::ostream &ostream, Matrix &rhs) {
    for (int i = 0; i < rhs.m_rows; ++i) {
        for (int j = 0; j < rhs.m_cols; ++j) {
            ostream << std::setw(3) << rhs(i, j) << ' ';
        }
        ostream << std::endl;
    }
    return ostream;
}

Matrix Matrix::operator+(const Matrix& rhs) {
    assert(m_rows == rhs.m_rows);
    assert(m_cols == rhs.m_cols);

    Matrix result = Matrix(m_rows, m_cols);

    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            result(i, j) = ((*this)(i, j) + rhs(i, j));
        }
    }

    return result;
}

Matrix Matrix::operator-(const Matrix& rhs) {
    assert(m_rows == rhs.m_rows);
    assert(m_cols == rhs.m_cols);

    Matrix result = Matrix(m_rows, m_cols);

    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            result(i, j) = ((*this)(i, j) - rhs(i, j));
        }
    }

    return result;
}

// This method ended up being slower and for big matrices ended up with stack overflow.
/*void Matrix::multiply(const Matrix &matrixA, const Matrix &matrixB, Matrix &matrixC) {
    static int i = 0, j = 0, k = 0;

    if (i >= matrixA.m_rows)
        return;

    if (j < matrixB.m_cols) {
        if (k < matrixA.m_cols) {
            matrixC(i, j) += (matrixA(i, k) * matrixB(k, j));
            ++k;

            multiply(matrixA, matrixB, matrixC);
        }

        k = 0;
        ++j;
        multiply(matrixA, matrixB, matrixC);
    }

    j= 0;
    ++i;
    multiply(matrixA, matrixB, matrixC);
}*/

void Matrix::multiply(const Matrix &matrixA, const Matrix &matrixB, Matrix &matrixC) {
    for (int i = 0; i < matrixA.m_rows; i++) {
        for (int j = 0; j < matrixB.m_cols; j++) {
            matrixC(i, j) = 0;

            for (int k = 0; k < matrixB.m_rows; k++) {
                matrixC(i, j) += matrixA(i, k) * matrixB(k, j);
            }
        }
    }
}

Matrix Matrix::operator*(const Matrix &rhs) {
    assert(m_cols == rhs.m_rows);

    Matrix result = Matrix(m_rows, rhs.m_cols);
    multiply((*this), rhs, result);

    return result;
}

Matrix::Matrix(int rows, int cols, int *data):
    m_rows(rows),
    m_cols(cols),
    m_data(new int[rows*cols])
{
    std::copy(data, data + (rows*cols), m_data.get());
}
