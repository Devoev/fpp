#include <Eigen/Dense>

namespace fem::geo {

    /**
     * Calculates the area of a 2D triangle defined by the given nodes.
     */
    double area_tri_2d(const Eigen::Matrix<double, 3, 2>& nodes) {
        return 0.5 * std::abs(
                (nodes(0,0) - nodes(1,0))*(nodes(1,0) - nodes(2,0))
                - (nodes(0,1) - nodes(1,1))*(nodes(1,1) - nodes(2,1))
        );
    }

    /**
     * Calculates the jacobian matrix of the map between a 2D triangle and the reference triangle.
     * @param nodes Node coordinates of the triangle.
     */
    Eigen::Matrix2d jacobian_tri_2d(const Eigen::Matrix<double, 3, 2>& nodes) {
        Eigen::Vector2d a0 = nodes.row(0);
        Eigen::Vector2d a1 = nodes.row(1);
        Eigen::Vector2d a2 = nodes.row(2);

        Eigen::Matrix2d J;
        J << a1 - a0, a2 - a0;
        return J;
    }

    /**
     * Calculates the inverse gram matrix of the map between a 2D triangle and the reference triangle.
     * @param nodes Node coordinates of the triangle.
     */
    Eigen::Matrix2d gram_inv_tri_2d(const Eigen::Matrix<double, 3, 2>& nodes) {
        Eigen::Matrix2d J = jacobian_tri_2d(nodes);
        return (J.transpose() * J).inverse();
    }
}
