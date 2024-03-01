#include <Eigen/Sparse>
#include <Eigen/Dense>
#include "nodal_basis.h"

namespace fem::mat::nodal {

    /**
     * Assembles a global nodal matrix. Loops over the mesh's triangular elements in parallel.
     * @param msh 2D triangular mesh object.
     * @param build_local Builder function for local matrix.
     * @return Sparse assembled matrix.
     */
    Eigen::MatrixXd assemble(
            const fem::mesh::TriangularMesh2D& msh,
            const std::function<Eigen::Matrix3d(const Eigen::Matrix<double, 3, 2>&)>& build_local) {

        Eigen::SparseMatrix<double> A(msh.N(), msh.N());

        // Iteration over triangles
        #pragma omp parallel for
        for (int t = 0; t < msh.T(); ++t) {
            auto nodes = msh.elems_to_nodes.row(t);
            auto coords = msh.nodes(nodes, Eigen::all);
            Eigen::Matrix3d M_t = build_local(coords);

            // Iteration over local matrix entries
            for (int i = 0; i < 3; ++i) {
                Eigen::Index ni = nodes[i];
                for (int j = 0; j < 3; ++j) {
                    Eigen::Index nj = nodes[j];
                    #pragma omp critical
                    { A.coeffRef(ni, nj) += M_t(i, j); };
                }
            }
        }

        return A;
    }

    /**
     * Creates the local mass matrix for nodal basis functions.
     * @param nodes Node coordinates.
     */
    Eigen::Matrix3d mass_local(const Eigen::Matrix<double, 3, 2>& nodes) {
        double val = geo::area_tri_2d(nodes) / 12;
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
        return assemble(msh, mass_local);
    }

    /**
     * Creates the local stiffness matrix for nodal basis functions.
     * @param nodes Node coordinates.
     */
    Eigen::Matrix3d stiffness_local(const Eigen::Matrix<double, 3, 2>& nodes) {
        double S = fem::geo::area_tri_2d(nodes);
        Eigen::Matrix2d G_inv = fem::geo::gram_inv_tri_2d(nodes);
        auto grad = fem::basis::nodal::grad_ref(nodes);
        return S * grad.transpose() * G_inv * grad;
    }

    /**
     * Assembles the global stiffness matrix for nodal basis functions.
     * @param msh 2D triangular mesh object.
     */
    Eigen::MatrixXd stiffness(const fem::mesh::TriangularMesh2D& msh) {
        return assemble(msh, stiffness_local);
    }
}
