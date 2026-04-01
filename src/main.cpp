#include "core/ecs/componentregistry.hpp"
#include <loader/png.hpp>
#include <renderer/opengl/texture.hpp>
#include <iostream>
#include <GLFW/glfw3.h>

#include <core/window.hpp>
#include <renderer/opengl/opengl.hpp>
#include <renderer/opengl/shader.hpp>
#include <renderer/opengl/mesh.hpp>
#include <util/file.hpp>
#include <loader/png.hpp>

#include <core/ecs/query.hpp>

std::vector<float> vertices = {
    -0.5f, -0.5f, 0.0f, -1.0f, -1.0f,
    -0.5f, 0.5f, 0.0f, -1.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 1.0f, -1.0f
};

std::vector<unsigned int> indices = {
    0, 1, 2, 2, 3, 0
};

struct Position {
    float x;
    float y;
    float z;
};

int main() {
    // Window window("Singularity", 1280, 720, false);
    // if (!window.init()) {
    //     std::cerr << "Failed to create GLFW window" << std::endl;
    //     return 1;
    // }

    // if (!OpenGL::init(1280, 720)) {
    //     std::cerr << "Failed to init OpenGL" << std::endl;
    //     return 1;
    // }

    // std::string vertexShader = readFile("res/vertex.glsl");
    // std::string fragmentShader = readFile("res/fragment.glsl");

    // std::expected<Shader, std::string> shaderExpected = Shader::loadFromGLSL(vertexShader, fragmentShader);
    // if (!shaderExpected.has_value()) {
    //     std::cerr << "Failed to compile shader: " << shaderExpected.error() << std::endl;
    //     return 1;
    // }
    // Shader shader = shaderExpected.value();

    // Mesh mesh(vertices, indices, {3, 2});

    // std::expected<Image, std::string> imageExpected = PNG::loadFromFile("res/dirt.png");
    // if (!imageExpected.has_value()) {
    //     std::cerr << "Failed to load image: " << imageExpected.error() << std::endl;
    //     return 1;
    // }
    // Image image = imageExpected.value();

    // std::expected<Texture, std::string> textureExpected = Texture::loadFromImage(image);
    // if (!textureExpected.has_value()) {
    //     std::cerr << "Failed to create texture: " << textureExpected.error() << std::endl;
    //     return 1;
    // }
    // Texture texture = textureExpected.value();

    // while (!window.shouldClose()) {
    //     glfwPollEvents();

    //     OpenGL::clear(0.15f, 0.15f, 0.15f);

    //     shader.use();
    //     texture.bind(0);
    //     mesh.draw();

    //     window.update();
    // }

    // mesh.destroy();
    // shader.destroy();

    Position position {1.0f, 1.0f, 0.0f};

    ComponentRegistry registry;
    registry.registerComponent<Position>();

    auto storage = static_cast<ComponentStorage<Position>*>(registry.getStorage<Position>());
    storage->insert(1, position);

    Query<Position> q(registry);
    for (auto& [pos] : q.query()) {
        std::cout << pos->x << std::endl;
    }

    return 0;
}
