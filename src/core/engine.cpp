#include "engine.hpp"
#include "render/renderer.hpp"
#include <util/types.hpp>
#include <util/consts.hpp>
#include <logger/logger.hpp>
#include <core/time.hpp>

namespace singularity {

Engine* Engine::instance;

Engine::Engine(const std::string& title, int width, int height, RendererType rendererType) : window(title, width, height, rendererType), input(window), renderer(rendererType) {
    instance = this;
}

Engine::~Engine() {
    if (instance == this) instance = nullptr;
}

bool Engine::init() {
    if (!window.init())
        return false;

    if (!input.init())
        return false;

    if (!renderer.init())
        return false;

    Log::info() << "Singularity engine " << VERSION;

    return true;
}

void Engine::destroy() {
    scene.destroy();

    renderer.destroy();
    input.destroy();
    window.destroy();

    Log::info() << "Exiting!";
}

Engine* Engine::getInstance() {
    return instance;
}

Input& Engine::getInput() {
    return input;
}

Window& Engine::getWindow() {
    return window;
}

Renderer& Engine::getRenderer() {
    return renderer;
}

Scene& Engine::getScene() {
    return scene;
}

void Engine::update() {
    Time::time = Window::getTime();
    Time::deltaTime = Time::time - Time::_lastTime;
    Time::_lastTime = Time::time;

    input.update();

    if (input.isShouldClose()) isRunning = false;

    renderer.clear(0, 0, 0);

    scene.update();

    window.update();
}

void Engine::run() {
    isRunning = true;
    while (isRunning) {
        update();
    }
}

}