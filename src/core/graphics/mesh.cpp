#include "mesh.hpp"
#include <core/engine.hpp>
#include <cstddef>
#include <logger/logger.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>

namespace singularity {

Mesh::Mesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& uvs, const std::vector<glm::vec3>& normals, const std::vector<unsigned int>& indices)
    : vertices(vertices), uvs(uvs), normals(normals), indices(indices) {}

bool Mesh::create() {
    if (Engine::getInstance() == nullptr) {
        Log::error() << "No engine instance!";
        return false;
    }

    size_t count = vertices.size() * 3 + uvs.size() * 2 + normals.size() * 3;
    std::vector<float> vbo;

    for (int i = 0; i < vertices.size(); i++) {
        vbo.push_back(vertices[i].x);
        vbo.push_back(vertices[i].y);
        vbo.push_back(vertices[i].z);
        vbo.push_back(uvs[i].x);
        vbo.push_back(uvs[i].y);
        vbo.push_back(normals[i].x);
        vbo.push_back(normals[i].y);
        vbo.push_back(normals[i].z);
    }

    mesh = Engine::getInstance()->getRenderer().createMesh();
    if (!mesh) return false;
    return mesh->create(vbo, indices, {3, 2, 3});
}

void Mesh::draw() {
    if (mesh) mesh->draw();
}

void Mesh::destroy() {
    if (mesh) mesh->destroy();
}

void Mesh::recalculateNormals() {
    normals.clear();
    normals.resize(vertices.size(), glm::vec3(0.0f));

    for (size_t i = 0; i < indices.size(); i += 3) {
        uint32_t i0 = indices[i + 0];
        uint32_t i1 = indices[i + 1];
        uint32_t i2 = indices[i + 2];

        const glm::vec3& v0 = vertices[i0];
        const glm::vec3& v1 = vertices[i1];
        const glm::vec3& v2 = vertices[i2];

        glm::vec3 edge1 = v1 - v0;
        glm::vec3 edge2 = v2 - v0;

        glm::vec3 faceNormal = glm::cross(edge1, edge2);

        normals[i0] += faceNormal;
        normals[i1] += faceNormal;
        normals[i2] += faceNormal;
    }

    for (glm::vec3& normal : normals) {
        if (glm::length2(normal) > 0.0f)
            normal = glm::normalize(normal);
        else
            normal = glm::vec3(0.0f, 1.0f, 0.0f);
    }
}

}