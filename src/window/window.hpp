#ifndef SINGULARITY_WINDOW_HPP
#define SINGULARITY_WINDOW_HPP

#include <window/windowevent.hpp>
#include <string>
#include <SDL3/SDL.h>
#include <util/types.hpp>

namespace singularity {

class Window {
public:
    Window(const std::string& title, unsigned int width, unsigned int height, RendererType rendererType);
    ~Window();

    bool init();
    void destroy();

    void update();

    bool pollEvent(WindowEvent& event);

    static void* getGLProcLoader();
    static double getTime();

private:
    std::string title;
    unsigned int width, height;
    RendererType rendererType;

    SDL_Window* window;
};

}

#endif