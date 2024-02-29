#include <iostream>
#include "fem/mesh/TriangularMesh2D.h"
#include "fem/util/geo.h"
#include "fem/matrix/nodal_mat.h"


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
//    auto msh = example_mesh();
    auto msh = fem::mesh::TriangularMesh2D::parse("../examples/unit_circle.msh");
    std::cout << msh.N() << " nodes and " << msh.T() << " triangles" << std::endl;

    auto M = fem::mat::nodal::mass(msh);
    auto K = fem::mat::nodal::stiffness(msh);
    std::cout << "Mass matrix M =  " << std::endl << M << std::endl;
    std::cout << "Stiffness matrix K =  " << std::endl << K << std::endl;

    return 0;
}
