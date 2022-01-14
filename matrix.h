//
// Created by ploca14 on 03.12.21.
//

#ifndef SEMESTRALKA_MATRIX_H
#define SEMESTRALKA_MATRIX_H

#include <memory>

class Matrix {
    int m_rows, m_cols;
    std::unique_ptr<int []> m_data;

    int index(int row, int col) const;
    void multiply(const Matrix &matrixA, const Matrix &matrixB, Matrix &matrixC);
public:
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, int* data);

    int& operator() (int row, int col);
    int operator() (int row, int col) const;

    Matrix operator+(const Matrix&);
    Matrix operator-(const Matrix&);
    Matrix operator*(const Matrix&);

    friend std::ostream& operator<<(std::ostream&, Matrix&);

    int get_rows() const {
        return m_rows;
    }

    int get_cols() const {
        return m_cols;
    }

    Matrix split(int i, int i1, int i2, int cols, const Matrix &matrix);
};

#endif //SEMESTRALKA_MATRIX_H
