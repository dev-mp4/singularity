#include "mesh.hpp"
#include <core/engine.hpp>
#include <logger/logger.hpp>

namespace singularity {

Mesh::Mesh(const std::vector<float>& _vertices, const std::vector<float>& uvs, const std::vector<unsigned int>& indices) : indices(indices), mesh(nullptr) {
    for (int i = 0; i < (_vertices.size() / 3); i++) {
        int vertex = i * 3;
        int uv = i * 2;
        vertices.push_back(_vertices[vertex]);
        vertices.push_back(_vertices[vertex + 1]);
        vertices.push_back(_vertices[vertex + 2]);
        vertices.push_back(uvs[uv]);
        vertices.push_back(uvs[uv + 1]);
    }
}

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) : vertices(vertices), indices(indices), mesh(nullptr) {}

bool Mesh::create() {
    if (Engine::getInstance() == nullptr) {
        Log::error() << "No engine instance!";
        return false;
    }

    mesh = Engine::getInstance()->getRenderer().createMesh(vertices, indices, {3, 2});
    return mesh != nullptr;
}

void Mesh::draw() {
    if (mesh) mesh->draw();
}

void Mesh::destroy() {
    if (mesh) mesh->destroy();
}

}