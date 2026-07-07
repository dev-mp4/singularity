#include "renderer.hpp"
#include <render/opengl/glrenderer.hpp>

namespace singularity {

Renderer::Renderer(RendererType type) : type(type) {}
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
    return renderer->init();
}


}