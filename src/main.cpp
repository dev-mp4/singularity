#include "core/component.hpp"
#include "core/components/meshrenderer.hpp"
#include "core/graphics/mesh.hpp"
#include "core/graphics/shadermanager.hpp"
#include "core/graphics/material.hpp"
#include "core/graphics/texture2d.hpp"
#include "core/time.hpp"
#include "loader/png.hpp"
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
    0.0f, 0.0f, // bottom left (corresponds to -0.5f, -0.5f)
    0.0f, 1.0f, // top left    (corresponds to -0.5f,  0.5f)
    1.0f, 0.0f, // bottom right (corresponds to  0.5f, -0.5f)
    1.0f, 1.0f  // top right    (corresponds to  0.5f,  0.5f)
};

std::vector<unsigned int> indices = {
    0, 1, 3,
    0, 3, 2
};

using namespace singularity;

class MyComp : public Component {
public:
    COMPONENT(MyComp)

    Transform* transform;

    void onStart() override {
        transform = gameObject->getComponent<Transform>();
    }

    void onDestroy() override {
    }

    void onFrame() override {
        ImGui::Begin("Test");

        ImGui::Button("Rotate quad");
        if (ImGui::IsItemActive()) {
            transform->rotate(glm::vec3(0, 0, 15) * Time::deltaTime);
        }

        ImGui::End();
    }

    void onTick() override {

    }

    void afterFrame() override {

    }

    void onRender() override {

    }

    void afterTick() override {

    }
};

class Cam : public Component {
    COMPONENT(Cam)

public:
    glm::vec3 pos;

    Transform* transform;

    void onStart() override {
        transform = gameObject->getComponent<Transform>();
    }

    void onDestroy() override {
    }

    void onFrame() override {
        ImGui::Begin("Camera test");

        ImGui::SliderFloat("Position X" , &pos.x, -5.0f, 5.0f);
        ImGui::SliderFloat("Position Y" , &pos.y, -5.0f, 5.0f);
        ImGui::SliderFloat("Position Z" , &pos.z, -5.0f, 5.0f);

        transform->setPosition(pos);

        ImGui::End();
    }

    void onTick() override {

    }

    void afterFrame() override {

    }

    void onRender() override {

    }

    void afterTick() override {

    }
};

int main() {
    Engine engine("Singularity", 1280, 720, RendererType::OpenGL);
    if (!engine.init()) return 1;

    GameObject o("Object");

    o.addComponent<Transform>();
    o.addComponent<MyComp>();
    MeshRenderer* r = o.addComponent<MeshRenderer>();
    
    Material* mat = new Material(ShaderManager::getShader("shader"));
    mat->compileShader();

    r->material = mat;

    r->mesh = new Mesh(vertices, uvs, indices);
    r->mesh->create();

    Image image = PNG::loadFromFile("res/images/image.png");
    if (image.width == 0) return 1;

    Texture2D* tex = new Texture2D();
    tex->fromImage(image);

    mat->setTexture2D("tex0", *tex);

    GameObject cam("Camera");
    
    cam.addComponent<Camera>();
    Transform* t = cam.addComponent<Transform>();
    t->translate(-t->forward);
    cam.addComponent<Cam>();

    engine.getScene().addGameObject(std::move(o));
    engine.getScene().addGameObject(std::move(cam));

    engine.run();

    engine.destroy();

    return 0;
}