#include <glm/fwd.hpp>
#include <library/components/camera.hpp>
#include <library/components/entitymesh.hpp>
#include <library/components/transform.hpp>
#include <library/systems/camerasystem.hpp>
#include <library/systems/transformsystem.hpp>
#include <library/systems/entitymeshrenderer.hpp>
#include <core/resourceid.hpp>
#include <glm/detail/qualifier.hpp>
#include <renderer/ishader.hpp>
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
#include <logger/logger.hpp>

std::vector<float> vertices = {
    -0.5f, -0.5f, 0.0f, -1.0f, -1.0f,
    -0.5f, 0.5f, 0.0f, -1.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 1.0f, -1.0f
};

std::vector<unsigned int> indices = {
    0, 1, 2, 2, 3, 0
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

    Camera camera {.fov=75.0f};
    Transform camTransform {.position=glm::vec3(0, 0, 1), .rotation=glm::quat(1, 0, 0, 0), .scale=glm::vec3(1, 1, 1)};

    EntityMesh entMesh {.shader=shaderID, .texture=textureID, .mesh=meshID};
    Transform entTransform {.position=glm::vec3(0, 0, 0), .rotation=glm::quat(1, 0, 0, 0), .scale=glm::vec3(1, 1, 1)};

    auto ent = engine.world.entity("ent");
    ent.set<EntityMesh>(entMesh);
    ent.set<Transform>(entTransform);

    auto cam = engine.world.entity("cam");
    cam.set<Camera>(camera);
    cam.set<Transform>(camTransform);

    engine.world.system<Transform>().kind(Engine::PostUpdate).each(transformSystem);
    engine.world.system<Camera, Transform>().kind(Engine::PostUpdate).each(cameraSystem);
    engine.world.system<EntityMesh, Transform>().kind(Engine::Render).each(entityMeshRenderer);

    engine.run();

    engine.destroy();

    return 0;
}
