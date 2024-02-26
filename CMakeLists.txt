cmake_minimum_required(VERSION 3.27)
project(fpp)

set(CMAKE_CXX_STANDARD 17)

include_directories("C:/Users/devin/eigen-3.4.0")

add_executable(fpp main.cpp
        fem/mesh/TriangularMesh2D.h
)
