#ifndef SINGULARITY_MESH_HPP
#define SINGULARITY_MESH_HPP

#include <vector>

class Mesh {
public:
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned char>& attributes);
    ~Mesh();

    void draw();
    void destroy();

private:
    unsigned int vao, vbo, ebo, indicesCount;
};

#endif //SINGULARITY_MESH_HPP