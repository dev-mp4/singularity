#ifndef SINGULARITY_WINDOW_HPP
#define SINGULARITY_WINDOW_HPP

#include <string>
#include <SDL3/SDL.h>

namespace singularity {

class Window {
public:
    Window(const std::string& title, unsigned int width, unsigned int height);
    ~Window();

    bool init();
    void destroy();

    void update();

private:
    std::string title;
    unsigned int width, height;

    SDL_Window* window;
    SDL_Renderer* renderer;
};

}

#endif