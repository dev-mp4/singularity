#include "core/resourceid.hpp"
#include "renderer/ishader.hpp"
#include <core/engine.hpp>
#include <renderer/imesh.hpp>
#include <renderer/itexture.hpp>
#include <loader/png.hpp>
#include <renderer/opengl/texture.hpp>
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
    ResourceID<IShader>  shader;
    ResourceID<ITexture> texture;
    ResourceID<IMesh>    mesh;
};

int main() {
    Engine engine;
    if (!engine.init(RendererKind::OPENGL_CORE, "Singularity", 1280, 720, false)) {
        return 1;
    }

    engine.resourceManager.registerResource<IShader>();
    engine.resourceManager.registerResource<ITexture>();
    engine.resourceManager.registerResource<IMesh>();

    std::string vertexShader = readFile("res/vertex.glsl");
    std::string fragmentShader = readFile("res/fragment.glsl");

    Shader* shader = Shader::loadFromGLSL(vertexShader, fragmentShader);
    if (shader == nullptr)
        return 1;

    ResourceID<IShader> shaderID = engine.resourceManager.add<IShader>(shader);

    Mesh* mesh = Mesh::create(vertices, indices, {3, 2});

    ResourceID<IMesh> meshID = engine.resourceManager.add<IMesh>(mesh);

    Image* image = PNG::loadFromFile("res/dirt.png");
    if (image == nullptr)
        return 1;

    Texture* texture = Texture::loadFromImage(image);
    if (texture == nullptr)
        return 1;

    ResourceID<ITexture> textureID = engine.resourceManager.add<ITexture>(texture);

    MeshComponent meshComp {shaderID, textureID, meshID};
    
    engine.world.entity("ent").set<MeshComponent>(meshComp);

    engine.world.system<MeshComponent>().each([](MeshComponent& c){
        IShader* shader = Engine::getInstance()->resourceManager.get(c.shader);
        ITexture* texture = Engine::getInstance()->resourceManager.get(c.texture);
        IMesh* mesh = Engine::getInstance()->resourceManager.get(c.mesh);

        shader->use();
        texture->bind(0);
        mesh->draw();
    });

    engine.run();

    engine.destroy();

    return 0;
}
