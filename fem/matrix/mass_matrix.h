#include <Eigen/Sparse>
#include <Eigen/Dense>

namespace fem::mat::mass {

    /**
     * Creates the local mass matrix for nodal basis functions.
     * @param nodes Node coordinates.
     */
    Eigen::Matrix3d node_local(const Eigen::Matrix<double, 3, 2>& nodes) {
        double val = geo::area_triangle_2d(nodes) / 12;
        return Eigen::Matrix3d {
                { 2*val, val, val },
                { val, 2*val, val },
                { val, val, 2*val }
        };
    }
}
