#include "engine.hpp"
#include "flecs/addons/cpp/c_types.hpp"
#include <logger/logger.hpp>
#include <GLFW/glfw3.h>
#include <renderer/opengl/opengl.hpp>
#include <util/consts.hpp>

Engine* Engine::instance;
flecs::entity Engine::Update;
flecs::entity Engine::PostUpdate;
flecs::entity Engine::Render;
flecs::entity Engine::PostRender;

flecs::entity Engine::OnSpawn;

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
    Log::info() << "Singularity " << VERSION;
    
    this->rendererKind = rendererKind;

    if (!window.init(title, width, height, fullscreen)) return false;

    switch (rendererKind) {
        case RendererKind::OPENGL_CORE:
            if (!OpenGL::init(width, height)) return false;
            Log::info() << "Renderer: OpenGL Core";
    }

    Log::info() << "Window resolution: " << width << "x" << height;
    Log::info() << "Window title: " << title;

    world.reset();


    Update = world.entity("Update").add(flecs::Phase);
    PostUpdate = world.entity("PostUpdate").add(flecs::Phase).depends_on(Update);
    Render = world.entity("Render").add(flecs::Phase).depends_on(PostUpdate);
    PostRender = world.entity("PostRender").add(flecs::Phase).depends_on(Render);

    flecs::entity pipeline = world.pipeline().with(flecs::System).build();
    
    world.set_pipeline(pipeline);

    return true;
}

void Engine::destroy() {
    resourceManager.destroy();
    window.destroy();

    Log::info() << "Exiting!";
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
    Log::info() << "Starting main loop";

    while (running) {
        update();
    }

    world.quit();
}