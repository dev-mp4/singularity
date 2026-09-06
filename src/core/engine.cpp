#include "engine.hpp"
#include <core/devui/developerui.hpp>
#include <render/renderer.hpp>
#include <util/types.hpp>
#include <util/consts.hpp>
#include <logger/logger.hpp>
#include <core/time.hpp>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>

namespace singularity {

Engine* Engine::instance;

Engine::Engine(const std::string& title, int width, int height, RendererType rendererType) : window(title, width, height, rendererType), input(window), renderer(rendererType),
    devuiState(false) {
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

    if (!initImGui())
        return false;

    renderer.enableBlend();
    renderer.enableCulling();

    bus.subscribe<KeyEvent>(this, &Engine::onKey);
    bus.subscribe<QuitEvent>(this, &Engine::onQuit);

    Log::info() << "Singularity engine " << VERSION;

#ifdef SINGULARITY_DEV_BUILD
    Log::info() << "Running in developer mode";
#endif

    return true;
}

void Engine::destroy() {
    scene.destroy();

    if (renderer.getType() == RendererType::OpenGL) ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

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

EventBus& Engine::getEventBus() {
    return bus;
}

void Engine::update() {
    Time::time = Window::getTime();
    Time::deltaTime = Time::time - Time::_lastTime;
    Time::_lastTime = Time::time;

    input.update();
    renderer.clear(0, 0, 0);
    ImGuiNewFrame();

    scene.update();

    if (devuiState) {
        DeveloperUI::draw();
    }

    ImGui::Render();

    ImGuiDrawFrame();
    window.update();
}

void Engine::onKey(const KeyEvent& e) {
#ifdef SINGULARITY_DEV_BUILD
    if (e.isPressed && e.key == KeyCode::F12) {
        devuiState = !devuiState;
    }
#endif
}

void Engine::onQuit(const QuitEvent& e) {
    isRunning = false;
}

void Engine::run() {
    isRunning = true;
    while (isRunning) {
        update();
    }
}

void Engine::ImGuiNewFrame() {
    if (renderer.getType() == RendererType::OpenGL) ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void Engine::ImGuiDrawFrame() {
    if (renderer.getType() == RendererType::OpenGL) ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool Engine::initImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    if (renderer.getType() == RendererType::OpenGL) {
        ImGui_ImplSDL3_InitForOpenGL(window.getWindow(), window.getGLContext());
        ImGui_ImplOpenGL3_Init("#version 440 core");
    }

    return true;
}

void Engine::ImGuiPollEvent(SDL_Event* e) {
    ImGui_ImplSDL3_ProcessEvent(e);
}

}