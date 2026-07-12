#include "render/imesh.hpp"
#include "render/ishader.hpp"
#include <SDL3/SDL.h>
#include <window/window.hpp>
#include <util/types.hpp>
#include <render/renderer.hpp>
#include <core/engine.hpp>
#include <util/file.hpp>

std::vector<float> vertices = {
    -0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

std::vector<unsigned int> indices = {
    0, 1, 2
};

int main() {
    singularity::Engine engine("Singularity", 1280, 720, singularity::RendererType::OpenGL);
    if (!engine.init()) return 1;

    singularity::IShader* shader = engine.getRenderer().compileShader(singularity::readFile("res/shader.vsh"), singularity::readFile("res/shader.fsh"));
    if (!shader) {
        return 1;
    }

    singularity::IMesh* mesh = engine.getRenderer().createMesh(vertices, indices, {3});
    if (!mesh) {
        return 1;
    }

    engine.run();

    shader->destroy();
    mesh->destroy();

    engine.destroy();

    return 0;
}