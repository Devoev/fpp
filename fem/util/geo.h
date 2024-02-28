#include <Eigen/Dense>

namespace fem::geo {

    /**
     * Calculates the area of a 2D triangle defined by the given nodes.
     */
    double area_triangle_2d(const Eigen::Matrix<double, 3, 2>& nodes) {
        return 0.5 * std::abs(
                (nodes(0,0) - nodes(1,0))*(nodes(1,0) - nodes(2,0))
                - (nodes(0,1) - nodes(1,1))*(nodes(1,1) - nodes(2,1))
        );
    }
}
