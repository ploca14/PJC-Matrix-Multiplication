cmake_minimum_required(VERSION 3.20)
project(semestralka)

set(CMAKE_CXX_STANDARD 14)

add_executable(semestralka main.cpp matrix.cpp matrix.h cli.cpp cli.h)
