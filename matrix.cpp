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
    return m_step * row + col;
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
        m_step(cols),
        is_owner(true),
        m_data(new int[rows * cols])
{

    std::fill_n(m_data, rows*cols, 0);
}

std::ostream &operator<<(std::ostream &ostream, Matrix &rhs) {
    for (int i = 0; i < rhs.m_rows; ++i) {
        for (int j = 0; j < rhs.m_cols; ++j) {
            ostream << std::setw(4) << rhs(i, j) << " ";
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

/* NAIVE
 * This method uses the 3 for loops by definition
 * */
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

/* Strassen
 * This method uses the Strassen algorithm
 * Only works for NxN square matrices, where N is a number to the power of 2
 * */
void strassen(const Matrix &matrixA, const Matrix &matrixB, Matrix &matrixC) {
    if (matrixA.get_rows() <= 2) {
        return naive(matrixA, matrixB, matrixC);
    }

    int half = matrixA.get_rows() / 2;

    Matrix a = Matrix(0, 0, half, half, matrixA);
    Matrix b = Matrix(0, half, half, half, matrixA);
    Matrix c = Matrix(half, 0, half, half, matrixA);
    Matrix d = Matrix(half, half, half, half, matrixA);

    Matrix e = Matrix(0, 0, half, half, matrixB);
    Matrix f = Matrix(0, half, half, half, matrixB);
    Matrix g = Matrix(half, 0, half, half, matrixB);
    Matrix h = Matrix(half, half, half, half, matrixB);

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

bool isPowerOfTwo(int size) {
    return (size & (size - 1)) == 0;
}

Matrix Matrix::operator*(const Matrix &rhs) {
    assert(m_cols == rhs.m_rows);

    Matrix result = Matrix(m_rows, rhs.m_cols);
    if (m_rows == rhs.m_cols && isPowerOfTwo(m_rows)) {
        strassen((*this), rhs, result);
    } else {
        naive((*this), rhs, result);
    }

    return result;
}

Matrix::Matrix(int rows, int cols, int *data):
    m_rows(rows),
    m_cols(cols),
    m_step(cols),
    is_owner(true),
    m_data(new int[rows*cols])
{
    std::copy(data, data + (rows*cols), m_data);
}

Matrix::Matrix(int start_row, int start_col, int rows, int cols, const Matrix &orig):
    m_rows(rows),
    m_cols(cols),
    m_step(orig.m_step),
    is_owner(false),
    m_data(orig.m_data + orig.index(start_row, start_col))
{
    assert(start_row+rows <= orig.m_rows && start_col+cols <= orig.m_cols);
}

Matrix::~Matrix() {
    if (is_owner) {
        delete[] m_data;
    }
}
