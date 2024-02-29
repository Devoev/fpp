
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

    // NODES
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

    // ELEMS TO NODES
    auto elems_head = stois(lines[elems_idx + 1]);

    // Find the elem blocks that describe the different elements
    int num_elems_blocks = elems_head[0];
    std::vector<size_t> elems_blocks_idx(num_elems_blocks);
    elems_blocks_idx[0] = elems_idx + 2;
    for (int i = 1; i < num_elems_blocks; ++i) {
        std::string next_line = lines[elems_blocks_idx[i-1]];
        elems_blocks_idx[i] = elems_blocks_idx[i-1] + stois(next_line)[3] + 1;
    }

    // Find block for triangle elements
    size_t triangles_idx = elems_blocks_idx[num_elems_blocks - 1];  // TODO: In general do a search for tag `2`
    int T = stois(lines[triangles_idx])[3];
    size_t triangles_end_idx = triangles_idx + T + 1;

    Eigen::Matrix<int, Eigen::Dynamic, 3> elems_to_nodes(T, 3);
    std::vector<std::array<int, 3>> elems_unordered {};
    elems_unordered.reserve(T);

    for (size_t i = triangles_idx + 1; i < triangles_end_idx; ++i) {
        std::vector<int> nums = stois(lines[i]);
        elems_unordered.push_back({ nums[1], nums[2], nums[3] });
    }

    // TODO: Adjust order of elems_unordered!
    for (int i = 0; i < T; ++i) {
        elems_to_nodes.coeffRef(i, 0) = elems_unordered[i][0];
        elems_to_nodes.coeffRef(i, 1) = elems_unordered[i][1];
        elems_to_nodes.coeffRef(i, 2) = elems_unordered[i][2];
    }

    return TriangularMesh2D { nodes, elems_to_nodes }; // TODO: Not yet implemented
}

