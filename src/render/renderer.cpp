#include "renderer.hpp"
#include "opengl/gltexture2d.hpp"
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

ITexture2D* Renderer::createTextureFromImage(Image& image) {
    if (type == RendererType::OpenGL) {
        GLTexture2D* texture = new GLTexture2D();
        texture->fromImage(image);
        return texture;
    }
    return nullptr;
}

void Renderer::enableBlend() {
    if (!renderer) return;
    renderer->enableBlend();
}

void Renderer::disableBlend() {
    if (!renderer) return;
    renderer->disableBlend();
}

void Renderer::enableCulling() {
    if (!renderer) return;
    renderer->enableCulling();
}

void Renderer::disableCulling() {
    if (!renderer) return;
    renderer->disableCulling();
}

}