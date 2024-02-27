
#include "TriangularMesh2D.h"
#include <fstream>

using namespace fem::mesh;

TriangularMesh2D TriangularMesh2D::parse(const std::string &msh_path) {
    std::ifstream file(msh_path);
    std::string line;

    while (std::getline(file, line)) {
        // TODO: Parse line and find $Nodes section
    }

    return TriangularMesh2D {}; // TODO: Not yet implemented
}

