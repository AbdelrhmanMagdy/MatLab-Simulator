cmake_minimum_required(VERSION 3.9)
project(cMatrix)

set(CMAKE_CXX_STANDARD 11)

add_executable(cMatrix
        cMatrix.cpp
        cMatrix.h
        main.cpp
        Matlab.cpp
        Matlab.h)