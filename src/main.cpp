#include "core/component.hpp"
#include "core/graphics/mesh.hpp"
#include "core/time.hpp"
#include <core/graphics/shader.hpp>
#include <SDL3/SDL.h>
#include <window/window.hpp>
#include <util/types.hpp>
#include <render/renderer.hpp>
#include <core/engine.hpp>
#include <util/file.hpp>
#include <core/component.hpp>
#include <core/gameobject.hpp>
#include <logger/logger.hpp>
#include <core/components/transform.hpp>

std::vector<float> vertices = {
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f,  // top left
    0.5f, -0.5f, 0.0f,  // bottom right
    0.5f, 0.5f, 0.0f, // top right
};

std::vector<float> uvs = {
    -1.0f, -1.0f,
    -1.0f, 1.0f,
    1.0f, -1.0f,
    1.0f, 1.0f
};

std::vector<unsigned int> indices = {
    0, 1, 3, 0, 2, 3
};

using namespace singularity;

class MyComp : public Component {
public:
    COMPONENT(MyComp)

    Mesh* mesh;
    Shader* shader;
    Transform* transform;

    void onStart() {
        shader = new Shader(readFile("res/shader.vsh"), readFile("res/shader.fsh"));
        shader->compile();

        mesh = new Mesh(vertices, uvs, indices);
        mesh->create();

        transform = gameObject->getComponent<Transform>();
    }

    void onDestroy() {
        shader->destroy();
        mesh->destroy();
    }

    void onFrame() {
        transform->rotate(glm::vec3(0, 0, 15) * Time::deltaTime);

        shader->use();
        shader->setMat4("vModelMatrix", transform->getMatrix());
        mesh->draw();
    }

    void onTick() {

    }

    void afterFrame() {

    }

    void afterTick() {

    }
};

int main() {
    Engine engine("Singularity", 1280, 720, RendererType::OpenGL);
    if (!engine.init()) return 1;

    GameObject o("Object");

    o.addComponent<Transform>();
    o.addComponent<MyComp>();

    engine.getScene().addGameObject(std::move(o));

    engine.run();

    engine.destroy();

    return 0;
}