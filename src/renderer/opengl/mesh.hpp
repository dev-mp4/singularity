#ifndef SINGULARITY_MESH_HPP
#define SINGULARITY_MESH_HPP

#include <vector>
#include <renderer/imesh.hpp>

class Mesh : public IMesh {
public:
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned char>& attributes);
    ~Mesh() override;

    void draw() override;
    void destroy() override;

private:
    unsigned int vao, vbo, ebo, indicesCount;
};

#endif //SINGULARITY_MESH_HPP