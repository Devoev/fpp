#include <iostream>
#include "fem/mesh/Mesh2D.h"

int main() {

    Eigen::Matrix<double, Eigen::Dynamic, 2> nodes(4, 2);
    nodes << 0, 0, 1, 0, 0, 1, 1, 1;

    Eigen::Matrix<int, Eigen::Dynamic, 3> elems_to_nodes(2, 3);
    elems_to_nodes << 0, 1, 2, 1, 2, 3;

    Mesh2D mesh { nodes, elems_to_nodes };

    std::cout << mesh.nodes << std::endl;
    std::cout << mesh.elems_to_nodes << std::endl;

    return 0;
}
