#ifndef SINGULARITY_ENGINE_HPP
#define SINGULARITY_ENGINE_HPP

#include <core/window.hpp>
#include <core/resourcemanager.hpp>
#include <flecs.h>

enum class RendererKind {
    OPENGL_CORE
};

class Engine {
public:
    Engine();
    ~Engine();

    static Engine* getInstance();

    flecs::world world;

    ResourceManager resourceManager;

    Window window;

    bool init(RendererKind rendererKind, const std::string& title, int width, int height, bool fullscreen);
    void destroy();

    void clear(float r, float g, float b);

    void update();

    void run();

    float deltaTime;
    float time;

    bool running;
    
    static flecs::entity Update;
    static flecs::entity PostUpdate;
    static flecs::entity Render;
    static flecs::entity PostRender;

    static flecs::entity OnSpawn;

private:
    static Engine* instance;

    RendererKind rendererKind;

    float lastTime;
};

#endif // SINGULARITY_ENGINE_HPP