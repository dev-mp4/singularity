#include "core/component.hpp"
#include "core/components/meshrenderer.hpp"
#include "core/graphics/mesh.hpp"
#include "core/graphics/shadermanager.hpp"
#include "core/material.hpp"
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
#include <imgui.h>

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

    Transform* transform;

    void onStart() {
        transform = gameObject->getComponent<Transform>();

        Log::warn() << "Warning! Too big cock!";
        Log::error() << "Error! Critically big cock!";
    }

    void onDestroy() {
    }

    void onFrame() {
        ImGui::Begin("Test");

        ImGui::Button("Rotate quad");
        if (ImGui::IsItemActive()) {
            transform->rotate(glm::vec3(0, 0, 15) * Time::deltaTime);
        }

        ImGui::End();
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
    o.addComponent<MeshRenderer>();

    MeshRenderer* r = o.getComponent<MeshRenderer>();
    
    Material* mat = new Material(ShaderManager::getShader("shader"));
    mat->compileShader();

    r->material = mat;

    mat->setFloat("light", 0.75f);

    r->mesh = new Mesh(vertices, uvs, indices);
    r->mesh->create();

    engine.getScene().addGameObject(std::move(o));

    engine.run();

    engine.destroy();

    return 0;
}