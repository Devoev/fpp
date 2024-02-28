#include <iostream>
#include "fem/mesh/TriangularMesh2D.h"
#include "fem/util/geo.h"
#include "fem/matrix/mass_matrix.h"


fem::mesh::TriangularMesh2D example_mesh() {
    Eigen::Matrix<double, 5, 2> nodes(5, 2);
    nodes << 0, 0,
            0, 1,
            1, 1,
            1, 0,
            0.5, 0.5;

    Eigen::Matrix<int, 5, 3> elems_to_nodes(5, 3);
    elems_to_nodes << 0, 1, 3,
                    1, 4, 0,
                    0, 4, 3,
                    2, 4, 1,
                    3, 4, 2;

    return fem::mesh::TriangularMesh2D { nodes, elems_to_nodes };
}



int main() {

    Eigen::Matrix<double, Eigen::Dynamic, 2> nodes(4, 2);
    nodes << 0, 0, 1, 0, 0, 1, 1, 1;

    Eigen::Matrix<int, Eigen::Dynamic, 3> elems_to_nodes(2, 3);
    elems_to_nodes << 0, 1, 2, 1, 2, 3;

    fem::mesh::TriangularMesh2D msh { nodes, elems_to_nodes };

    auto msh2 = example_mesh();
    std::cout << msh2.N() << " nodes and " << msh2.T() << " triangles" << std::endl;

    Eigen::Matrix<double, 3, 2> coords(3,2);
    coords << 0, 0, 1, 0, 0, 1;
    std::cout << fem::geo::area_triangle_2d(coords) << std::endl;
    std::cout << fem::mat::mass::node_local(coords) << std::endl;

    return 0;
}
