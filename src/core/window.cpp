#include "window.hpp"
#include <SDL3/SDL.h>
#include <logger/logger.hpp>

namespace singularity {

Window::Window(const std::string& title, unsigned int width, unsigned int height, RendererType rendererType) : title(title), width(width), height(height), window(nullptr), rendererType(rendererType) {}
Window::~Window() {}

bool Window::init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        Log::error() << "Failed to init SDL: " << SDL_GetError();
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title.c_str());
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, width);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, height);
    SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_OPENGL_BOOLEAN, true);

    window = SDL_CreateWindowWithProperties(props);

    if (!window) {
        Log::error() << "Failed to create SDL window: " << SDL_GetError();
        SDL_DestroyProperties(props);
        SDL_Quit();
        return false;
    }

    SDL_DestroyProperties(props);

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        Log::error() << "Failed to create OpenGL context: " << SDL_GetError();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    SDL_GL_SetSwapInterval(0);

    return true;
}

void Window::destroy() {
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void Window::update() {
    SDL_GL_SwapWindow(window);
}

void* Window::getGLProcLoader() {
    return (void*) SDL_GL_GetProcAddress;
}

}