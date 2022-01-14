//
// Created by ploca14 on 03.12.21.
//

#include "matrix.h"
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

/* RECURSIVE
 * This method ended up being slower and for bigger matrices ended up with stack overflow.
 * */
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

void naive(const Matrix &matrixA, const Matrix &matrixB, Matrix &matrixC) {
    for (int i = 0; i < matrixA.get_rows(); i++) {
        for (int j = 0; j < matrixB.get_cols(); j++) {
            matrixC(i, j) = 0;

            for (int k = 0; k < matrixB.get_rows(); k++) {
                matrixC(i, j) += matrixA(i, k) * matrixB(k, j);
            }
        }
    }
}

/* NAIVE
 * This method uses the 3 for loops by definition
 * */
/*void Matrix::multiply(const Matrix &matrixA, const Matrix &matrixB, Matrix &matrixC) {
    naive(matrixA, matrixB, matrixC);
}*/

/* Strassen
 * This method uses the Strassen algorithm
 * Only works for NxN square matrices, where N is a number to the power of 2
 * */
void Matrix::multiply(const Matrix &matrixA, const Matrix &matrixB, Matrix &matrixC) {
    if (matrixA.m_rows <= 2) {
        return naive(matrixA, matrixB, matrixC);
    }

    int half = matrixA.m_rows / 2;

    Matrix a = split(0, 0, half, half, matrixA);
    Matrix b = split(0, half, half, half, matrixA);
    Matrix c = split(half, 0, half, half, matrixA);
    Matrix d = split(half, half, half, half, matrixA);

    Matrix e = split(0, 0, half, half, matrixB);
    Matrix f = split(0, half, half, half, matrixB);
    Matrix g = split(half, 0, half, half, matrixB);
    Matrix h = split(half, half, half, half, matrixB);

    Matrix ae = a * e;
    Matrix bg = b * g;
    Matrix af = a * f;
    Matrix bh = b * h;
    Matrix ce = c * e;
    Matrix dg = d * g;
    Matrix cf = c * f;
    Matrix dh = d * h;

    Matrix c11 = ae + bg;
    Matrix c12 = af + bh;
    Matrix c21 = ce + dg;
    Matrix c22 = cf + dh;

    for (int i = 0; i < half; ++i) {
        for (int j = 0; j < half; ++j) {
            matrixC(i, j) = c11(i, j);
            matrixC(i, j + half) = c12(i, j);
            matrixC(i + half, j) = c21(i, j);
            matrixC(i + half, j + half) = c22(i, j);
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

Matrix Matrix::split(int start_row, int start_col, int rows, int cols, const Matrix &matrix) {
    Matrix result = Matrix(rows, cols);

    int i, ir, j, jr;
    for (i = start_row, ir = 0; ir < rows; ++i, ++ir) {
        for (j = start_col, jr = 0; jr < cols; ++j, ++jr) {
            result(ir, jr) = matrix(i, j);
        }
    }

    return result;
}
