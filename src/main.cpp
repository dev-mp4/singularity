#include "util/types.hpp"
#include <SDL3/SDL.h>
#include <core/window.hpp>
#include <util/types.hpp>
#include <render/renderer.hpp>

int main() {
    singularity::Window win("Singularity", 1280, 720, singularity::RendererType::OpenGL);
    if (!win.init()) {
        return 1;
    }

    singularity::Renderer rend(singularity::RendererType::OpenGL);
    if (!rend.init()) {
        return 1;
    }

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;

            rend.clear(1, 0, 0);

            win.update();
        }
    }

    win.destroy();

    return 0;
}