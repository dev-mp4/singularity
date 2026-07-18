#include "renderer.hpp"
#include "render/renderer.hpp"
#include <render/imesh.hpp>
#include <util/types.hpp>
#include <render/features.hpp>
#include <render/opengl/glrenderer.hpp>
#include <render/opengl/glshader.hpp>
#include <render/opengl/glmesh.hpp>

namespace singularity {

Renderer::Renderer(RendererType type) : type(type), features() {}
Renderer::~Renderer() {}

bool Renderer::init() {
    if (type == RendererType::OpenGL) return initGL();
    return false;
}

void Renderer::destroy() {
    if (!renderer) return;
    renderer->destroy();
}

void Renderer::clear(float r, float g, float b) {
    if (!renderer) return;
    renderer->clear(r, g, b);
}

bool Renderer::initGL() {
    renderer = new GLRenderer();
    features.isGLSLSupported = true;
    return renderer->init();
}

RendererFeatures Renderer::getFeatures() {
    return features;
}

RendererType Renderer::getType() {
    return type;
}

IShader* Renderer::compileShader(const std::string& vertex, const std::string& fragment) {
    if (type == RendererType::OpenGL) {
        GLShader* shader = new GLShader();
        if (shader->compileGLSL(vertex, fragment)) return shader;
        else return nullptr;
    }
    return nullptr;
}

IMesh* Renderer::createMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned short>& attributes) {
    if (type == RendererType::OpenGL) {
        GLMesh* mesh = new GLMesh();
        if (mesh->create(vertices, indices, attributes)) return mesh;
        else return nullptr;
    }
    return nullptr;
}

}