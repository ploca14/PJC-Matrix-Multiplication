//
// Created by ploca14 on 03.12.21.
//

#ifndef SEMESTRALKA_MATRIX_H
#define SEMESTRALKA_MATRIX_H

#include <memory>

class Matrix {
    int m_rows, m_cols;
    int m_step;
    int* m_data;
    bool is_owner;

    int index(int row, int col) const;
    void multiply(const Matrix &matrixA, const Matrix &matrixB, Matrix &matrixC);
public:
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, int* data);
    Matrix(int start_row, int start_col,
           int rows, int cols, const Matrix &orig);

    int& operator() (int row, int col);
    int operator() (int row, int col) const;

    virtual ~Matrix();

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
};

#endif //SEMESTRALKA_MATRIX_H
