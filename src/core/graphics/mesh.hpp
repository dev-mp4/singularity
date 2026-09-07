#ifndef SINGULARITY_MESH_HPP
#define SINGULARITY_MESH_HPP

#include <vector>
#include <render/imesh.hpp>
#include <glm/glm.hpp>

namespace singularity {

class Mesh {
public:
    Mesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& uvs, const std::vector<glm::vec3>& normals, const std::vector<unsigned int>& indices);
    ~Mesh();

    bool create();
    void draw();
    void destroy();

    void recalculateNormals();

private:
    IMesh* mesh;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;
};

}

#endif