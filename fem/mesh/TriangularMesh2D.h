
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
        Eigen::Matrix<double, Eigen::Dynamic, 2> nodes;

        /**
         * Element to node connection matrix.
         */
        Eigen::Matrix<int, Eigen::Dynamic, 3> elems_to_nodes;
    };
}


#endif //FPP_TRIANGULARMESH2D_H
