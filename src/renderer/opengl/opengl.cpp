#include "opengl.hpp"
#include <glad/glad.h>
#include <core/window.hpp>

namespace singularity {

bool OpenGL::init(int width, int height) {
    if (!gladLoadGLLoader((GLADloadproc)Window::getGLProcLoader())) {
        return false;
    }

    glViewport(0, 0, width, height);

    return true;
}

void OpenGL::clear(float r, float g, float b) {
    glClearColor(r, g, b, 255);
    glClear(GL_COLOR_BUFFER_BIT);
}

}