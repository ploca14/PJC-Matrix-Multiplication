//
// Created by ploca14 on 13.01.22.
//

#ifndef SEMESTRALKA_CLI_H
#define SEMESTRALKA_CLI_H

#include <iomanip>
#include <iostream>
#include <limits>
#include "matrix.h"

int inputInt(bool positive);

Matrix inputMatrix(int rows, int cols);

void user_multiply();

void random_multipy();

void print_help();

#endif //SEMESTRALKA_CLI_H
