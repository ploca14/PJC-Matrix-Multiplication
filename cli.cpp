//
// Created by ploca14 on 13.01.22.
//

#include <chrono>
#include <random>
#include "cli.h"

const int MAX = 1000;

Matrix generateRandomMatrix(int n, int m);

template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

int get_random_int() {
    static std::mt19937 mt{ std::random_device{}() };
    static std::uniform_int_distribution<> dist(1, MAX);
    return dist(mt);
}

void user_multiply() {
    std::cout << "MATRIX MULTIPLICATION" << std::endl << std::endl;
    std::cout << "First specify the size of the first matrix" << std:: endl;

    std::cout << "Number of rows: ";
    int a_rows = inputInt(true);
    std::cout << "Number of columns: ";
    int a_cols = inputInt(false);

    std::cout << std::endl;
    std::cout << "Now enter the values for the first matrix by rows, divided by spaces" << std:: endl;
    Matrix a = inputMatrix(a_rows, a_cols);

    std::cout << std::endl;
    std::cout << "Now specify the size of the second matrix" << std:: endl;

    std::cout << "Number of rows: ";
    int b_rows = inputInt(false);
    std::cout << "Number of columns: ";
    int b_cols = inputInt(false);

    std::cout << std::endl;
    std::cout << "Now enter the values for the second matrix by rows, divided by spaces" << std:: endl;
    Matrix b = inputMatrix(b_rows, b_cols);

    auto start = std::chrono::high_resolution_clock::now();
    Matrix product = a * b;
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::endl;
    std::cout << "The result is: " << std:: endl;
    std::cout << product << std::endl;
    std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
}

void random_multiply(int size) {
    int n, m, p;
    if (size > 0) {
        n = m = p = size;
    } else {
        n = get_random_int();
        m = get_random_int();
        p = get_random_int();
    }

    Matrix a = generateRandomMatrix(n, m);
    Matrix b = generateRandomMatrix(m, p);

    std::cout << "For two random matrices of size " << n << "x" << m  << " and " << m << "x" << p << std:: endl;

    auto start = std::chrono::high_resolution_clock::now();
    Matrix product = a * b;
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::endl;
    std::cout << "The result is: " << std:: endl;
    std::cout << product << std::endl;
    std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
}

Matrix generateRandomMatrix(int rows, int cols) {
    int* data = new int[rows*cols];

    for (int i = 0; i < rows*cols; ++i) {
        data[i] = get_random_int();
    }

    Matrix result = Matrix(rows, cols, data);
    delete[] data;

    return result;
}

void print_help() {
    std::cout << "Usage: semestralka [--help] [--random [<size>]] " << std::endl << std::endl;
    std::cout << "If you want to multiply random matrices:" << std::endl;
    std::cout << std::setw(30) << std::left << "  semestralka --random [<size>]" << "The program will generate two random matrices and multiply them" << std::endl << std::endl;
    std::cout << "If you want to input your matrices:" << std::endl;
    std::cout << std::setw(30) << std::left << "  semestralka  " << "The program will ask you to input two matrices and multiply them";
}

int inputInt(bool positive) {
    int a;

    std::cin >> a;
    while(true)
    {
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "You have entered wrong input" << std::endl;
            std::cin >> a;
        }
        if(!std::cin.fail()) {
            if (a <= 0) {
                std::cout << "You have to enter a positive number" << std::endl;
                continue;
            }
            if (a > MAX) {
                std::cout << "Maximum size of matrix is " << MAX << "x" << MAX  << std::endl;
                continue;
            }
            break;
        }
    }

    return a;
}

Matrix inputMatrix(int rows, int cols) {
    Matrix result = Matrix(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result(i, j) = inputInt(false);
        }
    }

    return result;
}