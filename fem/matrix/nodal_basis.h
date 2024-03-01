
#ifndef FPP_NODAL_BASIS_H
#define FPP_NODAL_BASIS_H

#include <Eigen/Dense>

namespace fem::basis::nodal {

    /**
     * Calculates the constant gradients of nodal basis functions on the reference triangle.
     */
    Eigen::Matrix<double, 2, 3> grad_ref(const Eigen::Matrix<double, 3, 2>& matrix) {
        return Eigen::Matrix<double, 3, 2> {
                { -1, -1 }, { 1, 0 }, { 0, 1 }
        }.transpose();
    }
}

#endif //FPP_NODAL_BASIS_H
