#ifndef SINGULARITY_GLMESH_HPP
#define SINGULARITY_GLMESH_HPP

#include <render/imesh.hpp>

namespace singularity {

class GLMesh : public IMesh {
public:
    GLMesh();
    ~GLMesh() override;

    bool create(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned short>& attributes) override;

    void draw() override;
    void destroy() override;

private:
    unsigned int vao, vbo, ebo, indicesCount;
};

}

#endif