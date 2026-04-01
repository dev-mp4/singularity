#include "window.hpp"

#include <GLFW/glfw3.h>

Window::Window(const std::string& title, int width, int height, bool fullscreen) : window(nullptr), title(title), width(width),
                                                                                   height(height), fullscreen(fullscreen) {}

Window::~Window() {
    glfwTerminate();
}

bool Window::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, title.c_str(), fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
    if (window == nullptr) {
        return false;
    }

    glfwMakeContextCurrent(window);
    return true;
}

void Window::update() {
    glfwSwapBuffers(window);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void* Window::getGLProcLoader() {
    return (void*) glfwGetProcAddress;
}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return height;
}