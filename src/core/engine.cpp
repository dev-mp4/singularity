#include "engine.hpp"
#include "render/renderer.hpp"
#include <util/types.hpp>
#include <util/consts.hpp>
#include <logger/logger.hpp>

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

void Engine::update() {
    input.update();

    if (input.isShouldClose()) isRunning = false;

    renderer.clear(0, 0, 0);

    window.update();
}

void Engine::run() {
    isRunning = true;
    while (isRunning) {
        update();
    }
}

}