
#include "TriangularMesh2D.h"
#include <fstream>
#include <iostream>

using namespace fem::mesh;

TriangularMesh2D TriangularMesh2D::parse(const std::string &msh_path) {
    std::ifstream file(msh_path);
    std::string line;
    std::vector<std::string> lines;

    if (!file) throw std::runtime_error("Could not open file at " + msh_path);

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    auto str_to_ints = [](const std::string& str){
        std::stringstream ss(str);
        std::vector<int> numbers;

        for(int i = 0; ss >> i;) {
            numbers.push_back(i);
        }
        return numbers;
    };

    size_t nodes_idx = std::find(lines.begin(), lines.end(), "$Nodes") - lines.begin();
    size_t end_nodes_idx = std::find(lines.begin(), lines.end(), "$EndNodes") - lines.begin();
    size_t elems_idx = std::find(lines.begin(), lines.end(), "$Elements") - lines.begin();
    size_t end_elems_idx = std::find(lines.begin(), lines.end(), "$EndElements") - lines.begin();

    // Nodes
    int N = str_to_ints(lines[nodes_idx + 1])[1];
    Eigen::Matrix<double, Eigen::Dynamic, 2> nodes(N, 2);

    for (size_t i = nodes_idx + 2; i < end_nodes_idx; ++i) {
//        std::cout << lines[i] << std::endl;
    }

    // Elems to nodes
    int T = str_to_ints(lines[elems_idx + 1])[1];
    Eigen::Matrix<int, Eigen::Dynamic, 3> elems_to_nodes(T, 3);

    for (size_t i = elems_idx + 2; i < end_elems_idx; ++i) {
//        std::cout << lines[i] << std::endl;
    }

    return TriangularMesh2D { nodes, elems_to_nodes }; // TODO: Not yet implemented
}

