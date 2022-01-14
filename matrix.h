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
};

#endif //SEMESTRALKA_MATRIX_H
