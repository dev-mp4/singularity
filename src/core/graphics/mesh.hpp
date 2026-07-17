#ifndef SINGULARITY_MESH_HPP
#define SINGULARITY_MESH_HPP

#include <vector>
#include <render/imesh.hpp>

namespace singularity {

class Mesh {
public:
    Mesh(const std::vector<float>& vertices, const std::vector<float>& uvs, const std::vector<unsigned int>& indices);
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    bool create();
    void draw();
    void destroy();

private:
    IMesh* mesh;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};

}

#endif