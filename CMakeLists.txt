cmake_minimum_required(VERSION 3.27)
project(fpp)

set(CMAKE_CXX_STANDARD 17)

include_directories("C:/Users/devin/eigen-3.4.0")

add_executable(fpp main.cpp
        fem/mesh/TriangularMesh2D.h
        fem/mesh/TriangularMesh2D.cpp
        fem/matrix/nodal_mat.h
        fem/util/geo.h
        fem/matrix/nodal_basis.h
)
