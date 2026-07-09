#include "core/input.hpp"
#include "core/keycode.hpp"
#include "util/types.hpp"
#include "window/windowevent.hpp"
#include <SDL3/SDL.h>
#include <window/window.hpp>
#include <util/types.hpp>
#include <render/renderer.hpp>

int main() {
    singularity::Window win("Singularity", 1280, 720, singularity::RendererType::OpenGL);
    if (!win.init()) {
        return 1;
    }
    singularity::Input input(win);
    if (!input.init()) {
        return 1;
    }

    singularity::Renderer rend(singularity::RendererType::OpenGL);
    if (!rend.init()) {
        return 1;
    }

    bool running = true;
    singularity::WindowEvent event;
    while (running) {
        input.update();

        if (input.isShouldClose()) running = false;
        if (input.getKeyDown(singularity::KeyCode::Escape)) running = false;
        
        rend.clear(1, 0, 0);

        win.update();
    }

    win.destroy();

    return 0;
}