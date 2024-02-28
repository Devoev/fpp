#include <Eigen/Sparse>
#include <Eigen/Dense>

namespace fem::mat::nodal {

    /**
     * Creates the local mass matrix for nodal basis functions.
     * @param nodes Node coordinates.
     */
    Eigen::Matrix3d mass_local(const Eigen::Matrix<double, 3, 2>& nodes) {
        double val = geo::area_triangle_2d(nodes) / 12;
        return Eigen::Matrix3d {
                { 2*val, val, val },
                { val, 2*val, val },
                { val, val, 2*val }
        };
    }

    /**
     * Assembles the global mass matrix for nodal basis functions.
     * @param msh 2D triangular mesh object.
     */
    Eigen::MatrixXd mass(const fem::mesh::TriangularMesh2D& msh) {
        Eigen::Index n = msh.N();
        Eigen::Index m = 9 * msh.T();
        Eigen::SparseMatrix<double> M(n,n);

        // Iteration over triangles
        for (int t = 0; t < msh.T(); ++t) {
            auto nodes = msh.elems_to_nodes.row(t);
            auto coords = msh.nodes(nodes, Eigen::all);
            auto M_t = mass_local(coords);

            // Iteration over local matrix entries
            for (int i = 0; i < 3; ++i) {
                Eigen::Index ni = nodes[i];
                for (int j = 0; j < 3; ++j) {
                    Eigen::Index nj = nodes[j];
                    M.coeffRef(ni, nj) += M_t(i,j);
                }
            }
        }

        return M;
    }

    /**
     * Assembles the global stiffness matrix for nodal basis functions.
     * @param msh 2D triangular mesh object.
     */
    Eigen::MatrixXd stiffness(const fem::mesh::TriangularMesh2D& msh) {
        Eigen::Index n = msh.N();
        Eigen::Index m = 9 * msh.T();
        Eigen::SparseMatrix<double> K(n, n);
        return K;
    }
}
