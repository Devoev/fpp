
#ifndef FPP_TRIANGULARMESH2D_H
#define FPP_TRIANGULARMESH2D_H

#include <Eigen/Dense>


namespace fem::mesh {

    /**
     * A 2-dimensional triangular mesh.
     */
    struct TriangularMesh2D {

        /**
         * Node coordinate matrix.
         */
        const Eigen::Matrix<double, Eigen::Dynamic, 2> nodes;

        /**
         * Element to node connection matrix.
         */
        const Eigen::Matrix<int, Eigen::Dynamic, 3> elems_to_nodes;

        /**
         * Number of nodes
         */
        [[nodiscard]] Eigen::Index N() const {
            return this->nodes.rows();
        }

        /**
         * Number of triangle elements.
         */
        [[nodiscard]] Eigen::Index T() const {
            return this->elems_to_nodes.rows();
        }

        /**
         * x-coordinates of nodes.
         */
        [[nodiscard]] Eigen::VectorXd x() const {
            return this->nodes.col(0);
        }

        /**
         * y-coordinates of nodes.
         */
        [[nodiscard]] Eigen::VectorXd y() const {
            return this->nodes.col(0);
        }
    };
}


#endif //FPP_TRIANGULARMESH2D_H
