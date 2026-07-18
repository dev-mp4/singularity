#ifndef SINGULARITY_ENGINE_HPP
#define SINGULARITY_ENGINE_HPP

#include <window/window.hpp>
#include <core/input.hpp>
#include <util/types.hpp>
#include <render/renderer.hpp>
#include <core/scene.hpp>
#include <string>

namespace singularity {

class Engine {
public:
    Engine(const std::string& title, int width, int height, RendererType rendererType);
    ~Engine();

    bool init();

    void destroy();
    
    static Engine* getInstance();

    Input& getInput();
    Window& getWindow();
    Renderer& getRenderer();
    Scene& getScene();

    void update();
    void run();

    void ImGuiNewFrame();
    void ImGuiDrawFrame();

    void ImGuiPollEvent(SDL_Event* e);

private:
    static Engine* instance;

    bool isRunning;

    Window window;
    Input input;

    Renderer renderer;

    Scene scene;

    bool devuiState;

    bool initImGui();
};

}

#endif