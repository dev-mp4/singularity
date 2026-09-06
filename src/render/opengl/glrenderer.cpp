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

void GLRenderer::enableBlend() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GLRenderer::disableBlend() {
    glDisable(GL_BLEND);
}

void GLRenderer::enableCulling() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
}

void GLRenderer::disableCulling() {
    glDisable(GL_CULL_FACE);
}


void GLRenderer::destroy() {
    // ...
}

void GLRenderer::clear(float r, float g, float b) {
    glClearColor(r, g, b, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

}