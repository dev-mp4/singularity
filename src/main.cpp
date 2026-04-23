#include <core/engine.hpp>
#include <renderer/imesh.hpp>
#include <renderer/itexture.hpp>
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

std::vector<float> vertices = {
    -0.5f, -0.5f, 0.0f, -1.0f, -1.0f,
    -0.5f, 0.5f, 0.0f, -1.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 1.0f, -1.0f
};

std::vector<unsigned int> indices = {
    0, 1, 2, 2, 3, 0
};

struct MeshComponent {
    IShader* shader;
    ITexture* texture;
    IMesh* mesh;
};

int main() {
    Engine engine;
    if (!engine.init(RendererKind::OPENGL_CORE, "Singularity", 1280, 720, false)) {
        return 1;
    }

    std::string vertexShader = readFile("res/vertex.glsl");
    std::string fragmentShader = readFile("res/fragment.glsl");

    Result<Shader> shaderResult = Shader::loadFromGLSL(vertexShader, fragmentShader);
    if (!shaderResult.hasValue()) {
        std::cerr << "Failed to compile shader: " << shaderResult.error() << std::endl;
        return 1;
    }
    Shader shader = shaderResult.value();

    Mesh mesh(vertices, indices, {3, 2});

    Result<Image> imageResult = PNG::loadFromFile("res/dirt.png");
    if (!imageResult.hasValue()) {
        std::cerr << "Failed to load image: " << imageResult.error() << std::endl;
        return 1;
    }
    Image image = imageResult.value();

    Result<Texture> textureResult = Texture::loadFromImage(image);
    if (!textureResult.hasValue()) {
        std::cerr << "Failed to create texture: " << textureResult.error() << std::endl;
        return 1;
    }
    Texture texture = textureResult.value();

    MeshComponent meshComp {&shader, &texture, &mesh};
    
    engine.world.entity("ent").set<MeshComponent>(meshComp);

    engine.world.system<MeshComponent>().each([](MeshComponent& c){
        c.shader->use();
        c.texture->bind(0);
        c.mesh->draw();
    });

    engine.run();

    mesh.destroy();
    shader.destroy();
    texture.destroy();

    engine.destroy();

    return 0;
}
