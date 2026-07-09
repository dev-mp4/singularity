#include "glrenderer.hpp"
#include <logger/logger.hpp>
#include <window/window.hpp>
#include <glad/glad.h>

namespace singularity {

GLRenderer::GLRenderer() {}
GLRenderer::~GLRenderer() {}

bool GLRenderer::init() {
    int version = gladLoadGLLoader((GLADloadproc) Window::getGLProcLoader());
    if (version == 0) {
        Log::error() << "Failed to load OpenGL!";
        return false;
    }

    Log::info() << glGetString(GL_VERSION);

    return true;
}

void GLRenderer::destroy() {
    // ...
}

void GLRenderer::clear(float r, float g, float b) {
    glClearColor(r, g, b, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

}