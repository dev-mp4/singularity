#include <SDL3/SDL.h>
#include <core/window.hpp>

int main() {
    singularity::Window win("Singularity", 1280, 720);
    if (!win.init()) {
        return 1;
    }

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;

            win.update();
        }
    }

    win.destroy();

    return 0;
}