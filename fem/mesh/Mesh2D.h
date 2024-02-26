
#ifndef FPP_MESH2D_H
#define FPP_MESH2D_H

#include <Eigen/Dense>


/**
 * A 2-dimensional triangular mesh.
 */
struct Mesh2D {

    /**
     * Node coordinate matrix.
     */
    Eigen::Matrix<double, Eigen::Dynamic, 2> nodes;

    /**
     * Element to node connection matrix.
     */
    Eigen::Matrix<int, Eigen::Dynamic, 3> elems_to_nodes;
};


#endif //FPP_MESH2D_H
