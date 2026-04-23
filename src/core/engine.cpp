#include "engine.hpp"
#include <GLFW/glfw3.h>
#include <renderer/opengl/opengl.hpp>

Engine* Engine::instance;

Engine::Engine() {
    instance = this;
}

Engine::~Engine() {
    instance = nullptr;
}

Engine* Engine::getInstance() {
    return instance;
}

bool Engine::init(RendererKind rendererKind, const std::string& title, int width, int height, bool fullscreen) {
    this->rendererKind = rendererKind;

    if (!window.init(title, width, height, fullscreen)) return false;

    switch (rendererKind) {
        case RendererKind::OPENGL_CORE:
            if (!OpenGL::init(width, height)) return false;
    }

    return true;
}

void Engine::destroy() {
    window.destroy();
}

void Engine::clear(float r, float g, float b) {
    switch (rendererKind) {
        case RendererKind::OPENGL_CORE:
            OpenGL::clear(r, g, b);
    }
}

void Engine::update() {
    glfwPollEvents();

    running = !window.shouldClose() && !world.should_quit();

    clear(0.0f, 0.0f, 0.0f);

    time = Window::getTime();
    deltaTime = time - lastTime;
    lastTime = time;

    world.progress();

    window.update();
}

void Engine::run() {
    while (running) {
        update();
    }

    world.quit();
}