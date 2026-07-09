#include "core/input.hpp"
#include "core/keycode.hpp"
#include "render/imesh.hpp"
#include "render/ishader.hpp"
#include "util/file.hpp"
#include "util/types.hpp"
#include "window/windowevent.hpp"
#include <SDL3/SDL.h>
#include <window/window.hpp>
#include <util/types.hpp>
#include <render/renderer.hpp>

std::vector<float> vertices = {
    -0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

std::vector<unsigned int> indices = {
    0, 1, 2
};

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

    singularity::IShader* shader = rend.compileShader(singularity::readFile("res/shader.vsh"), singularity::readFile("res/shader.fsh"));
    if (!shader) {
        return 1;
    }

    singularity::IMesh* mesh = rend.createMesh(vertices, indices, {3});
    if (!mesh) {
        return 1;
    }

    bool running = true;
    singularity::WindowEvent event;
    while (running) {
        input.update();

        if (input.isShouldClose()) running = false;
        if (input.getKeyDown(singularity::KeyCode::Escape)) running = false;

        rend.clear(0, 0, 0);

        shader->use();
        mesh->draw();

        win.update();
    }

    shader->destroy();
    mesh->destroy();

    win.destroy();

    return 0;
}