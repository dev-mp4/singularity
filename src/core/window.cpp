#include "window.hpp"

#include <GLFW/glfw3.h>

namespace singularity {

Window::Window() : window(nullptr) {}

Window::~Window() {}

bool Window::init(const std::string& title, int width, int height, bool fullscreen) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, title.c_str(), fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
    if (window == nullptr) {
        return false;
    }

    this->width = width;
    this->height = height;

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

double Window::getTime() {
    return glfwGetTime();
}

void Window::destroy() {
    glfwTerminate();
}

void Window::setKeyCallback(KeyCallbackFn callback) {
    glfwSetKeyCallback(window, (GLFWkeyfun)callback);
}

void Window::setMouseCallback(MouseCallbackFn callback) {
    glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)callback);
}

void Window::setMousePosCallback(CursorPosCallbackFn callback) {
    glfwSetCursorPosCallback(window, (GLFWcursorposfun)callback);
}

void Window::setCursorState(bool state) {
    glfwSetInputMode(window, GLFW_CURSOR, state ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

}