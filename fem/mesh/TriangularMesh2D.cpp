
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

    /**
     * Splits the given string at whitespaces.
     */
    auto split = [](const std::string& str){
        std::stringstream stream(str);
        std::vector<std::string> res;
        std::string tmp;

        while (std::getline(stream, tmp, ' ')) {
            res.push_back(tmp);
        }

        return res;
    };

    /**
     * Extracts integers from the given string.
     */
    auto stois = [&split](const std::string& str) {
        std::vector<int> nums;
        std::vector<std::string> s = split(str);
        std::transform(s.begin(), s.end(), std::back_inserter(nums), [](std::string& s){
            return std::stoi(s);
        });
        return nums;
    };

    /**
     * Extracts doubles from the given string.
     */
    auto stods = [&split](const std::string& str) {
        std::vector<double> nums;
        std::vector<std::string> s = split(str);
        std::transform(s.begin(), s.end(), std::back_inserter(nums), [](const std::string& s){
            return std::stod(s);
        });
        return nums;
    };

    size_t nodes_idx = std::find(lines.begin(), lines.end(), "$Nodes") - lines.begin();
    size_t end_nodes_idx = std::find(lines.begin(), lines.end(), "$EndNodes") - lines.begin();
    size_t elems_idx = std::find(lines.begin(), lines.end(), "$Elements") - lines.begin();
    size_t end_elems_idx = std::find(lines.begin(), lines.end(), "$EndElements") - lines.begin();

    // Nodes
    int N = stois(lines[nodes_idx + 1])[1];
    Eigen::Matrix<double, Eigen::Dynamic, 2> nodes(N, 2);
    std::vector<std::pair<double, double>> nodes_unordered {};
    nodes_unordered.reserve(N);

    for (size_t i = nodes_idx + 2; i < end_nodes_idx; ++i) {
        std::vector<double> nums = stods(lines[i]);
        if (nums.size() != 3) continue;
        nodes_unordered.emplace_back(nums[0], nums[1]);
    }

    // TODO: Adjust order of nodes_unordered!
    for (int i = 0; i < N; ++i) {
        nodes.coeffRef(i, 0) = nodes_unordered[i].first;
        nodes.coeffRef(i, 1) = nodes_unordered[i].second;
    }

    // Elems to nodes
    int T = stois(lines[elems_idx + 1])[1];
    Eigen::Matrix<int, Eigen::Dynamic, 3> elems_to_nodes(T, 3);

    for (size_t i = elems_idx + 2; i < end_elems_idx; ++i) {
//        std::cout << lines[i] << std::endl;
    }

    return TriangularMesh2D { nodes, elems_to_nodes }; // TODO: Not yet implemented
}

