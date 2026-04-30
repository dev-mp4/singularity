#ifndef SINGULARITY_MESH_HPP
#define SINGULARITY_MESH_HPP

#include <vector>
#include <renderer/imesh.hpp>

class Mesh : public IMesh {
public:
    Mesh(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int indicesCount);
    ~Mesh() override;

    void draw() override;
    static Mesh* create(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned char>& attributes);
    void destroy() override;

private:
    unsigned int vao, vbo, ebo, indicesCount;
};

#endif //SINGULARITY_MESH_HPP