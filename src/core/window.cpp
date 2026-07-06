#include "window.hpp"
#include <SDL3/SDL.h>
#include <logger/logger.hpp>

namespace singularity {

Window::Window(const std::string& title, unsigned int width, unsigned int height) : title(title), width(width), height(height), window(nullptr), renderer(nullptr) {}
Window::~Window() {}

bool Window::init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        Log::error() << "SDL init error: " << SDL_GetError();
        return false;
    }

    if (!SDL_CreateWindowAndRenderer(title.c_str(), width, height, 0, &window, &renderer)) {
        Log::error() << "SDL window/renderer creation error: " << SDL_GetError();
        SDL_Quit();
        return false;
    }

    return true;
}

void Window::destroy() {
    if (window && renderer) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void Window::update() {
    SDL_RenderPresent(renderer);
}

}