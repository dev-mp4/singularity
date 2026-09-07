#include "core/component.hpp"
#include "core/components/meshrenderer.hpp"
#include "core/engine.hpp"
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

std::vector<glm::vec3> vertices = {
    // Front face
    glm::vec3(-0.5f, -0.5f,  0.5f), // 0: Bottom-left
     glm::vec3(0.5f, -0.5f,  0.5f), // 1: Bottom-right
     glm::vec3(0.5f,  0.5f,  0.5f), // 2: Top-right
    glm::vec3(-0.5f,  0.5f,  0.5f), // 3: Top-left

    // Back face
     glm::vec3(0.5f, -0.5f, -0.5f), // 4: Bottom-left
    glm::vec3(-0.5f, -0.5f, -0.5f), // 5: Bottom-right
    glm::vec3(-0.5f,  0.5f, -0.5f), // 6: Top-right
     glm::vec3(0.5f,  0.5f, -0.5f), // 7: Top-left

    // Top face
    glm::vec3(-0.5f,  0.5f,  0.5f), // 8: Bottom-left
     glm::vec3(0.5f,  0.5f,  0.5f), // 9: Bottom-right
     glm::vec3(0.5f,  0.5f, -0.5f), // 10: Top-right
    glm::vec3(-0.5f,  0.5f, -0.5f), // 11: Top-left

    // Bottom face
    glm::vec3(-0.5f, -0.5f, -0.5f), // 12: Bottom-left
     glm::vec3(0.5f, -0.5f, -0.5f), // 13: Bottom-right
     glm::vec3(0.5f, -0.5f,  0.5f), // 14: Top-right
    glm::vec3(-0.5f, -0.5f,  0.5f), // 15: Top-left

    // Right face
     glm::vec3(0.5f, -0.5f,  0.5f), // 16: Bottom-left
     glm::vec3(0.5f, -0.5f, -0.5f), // 17: Bottom-right
     glm::vec3(0.5f,  0.5f, -0.5f), // 18: Top-right
     glm::vec3(0.5f,  0.5f,  0.5f), // 19: Top-left

    // Left face
    glm::vec3(-0.5f, -0.5f, -0.5f), // 20: Bottom-left
    glm::vec3(-0.5f, -0.5f,  0.5f), // 21: Bottom-right
    glm::vec3(-0.5f,  0.5f,  0.5f), // 22: Top-right
    glm::vec3(-0.5f,  0.5f, -0.5f)  // 23: Top-left
};

std::vector<glm::vec2> uvs = {
    // Front
    glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 0.0f),

    // Back
    glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 0.0f),

    // Top
    glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 0.0f),

    // Bottom
    glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 0.0f),

    // Right
    glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 0.0f),

    // Left
    glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 0.0f)
};

std::vector<uint32_t> indices = {
     0,  1,  2,   2,  3,  0, // Front
     4,  5,  6,   6,  7,  4, // Back
     8,  9, 10,  10, 11,  8, // Top
    12, 13, 14,  14, 15, 12, // Bottom
    16, 17, 18,  18, 19, 16, // Right
    20, 21, 22,  22, 23, 20  // Left
};

std::vector<glm::vec3> normals = {
    // Front (+Z)
     glm::vec3(0.0f,  0.0f,  1.0f),
     glm::vec3(0.0f,  0.0f,  1.0f),
     glm::vec3(0.0f,  0.0f,  1.0f),
     glm::vec3(0.0f,  0.0f,  1.0f),

    // Back (-Z)
     glm::vec3(0.0f,  0.0f, -1.0f),
     glm::vec3(0.0f,  0.0f, -1.0f),
     glm::vec3(0.0f,  0.0f, -1.0f),
     glm::vec3(0.0f,  0.0f, -1.0f),

    // Top (+Y)
     glm::vec3(0.0f,  1.0f,  0.0f),
     glm::vec3(0.0f,  1.0f,  0.0f),
     glm::vec3(0.0f,  1.0f,  0.0f),
     glm::vec3(0.0f,  1.0f,  0.0f),

    // Bottom (-Y)
     glm::vec3(0.0f, -1.0f,  0.0f),
     glm::vec3(0.0f, -1.0f,  0.0f),
     glm::vec3(0.0f, -1.0f,  0.0f),
     glm::vec3(0.0f, -1.0f,  0.0f),

    // Right (+X)
     glm::vec3(1.0f,  0.0f,  0.0f),
     glm::vec3(1.0f,  0.0f,  0.0f),
     glm::vec3(1.0f,  0.0f,  0.0f),
     glm::vec3(1.0f,  0.0f,  0.0f),

    // Left (-X)
    glm::vec3(-1.0f,  0.0f,  0.0f),
    glm::vec3(-1.0f,  0.0f,  0.0f),
    glm::vec3(-1.0f,  0.0f,  0.0f),
    glm::vec3(-1.0f,  0.0f,  0.0f)
};

using namespace singularity;

class MyComp : public Component {
public:
    COMPONENT(MyComp)

    Transform* transform;
    float speed = 15.0f;

    void onStart() override {
        transform = gameObject->getComponent<Transform>();
    }

    void onDestroy() override {
    }

    void onFrame() override {
        ImGui::Begin("Test");

        ImGui::Button("Rotate box");
        if (ImGui::IsItemActive()) {
            transform->rotate(glm::vec3(speed) * Time::deltaTime);
        }

        ImGui::SliderFloat("Speed", &speed, 0.0f, 100.0f);

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
    glm::vec3 pos{0.0f, 0.0f, 0.0f};
    glm::vec3 rot{0.0f, 0.0f, 0.0f}; // X: Pitch, Y: Yaw, Z: Roll (in degrees)

    float moveSpeed = 5.0f;
    float mouseSensitivity = 0.1f;

    Transform* transform = nullptr;

    void onStart() override {
        transform = gameObject->getComponent<Transform>();
        if (transform) {
            pos = transform->position;
            rot = transform->eulerAngles;
        }
    }

    void onDestroy() override {}

    void onFrame() override {
        if (!transform) return;

        Input& i = Engine::getInstance()->getInput();
        Window& w = Engine::getInstance()->getWindow();

        if (i.getMouseButton(3)) {

            rot.y -= i.getMouseDeltaX() * mouseSensitivity;
            rot.x -= i.getMouseDeltaY() * mouseSensitivity;

            rot.x = glm::clamp(rot.x, -89.0f, 89.0f);

            glm::vec3 moveDir(0.0f);

            if (i.getKey(KeyCode::W)) moveDir += transform->forward;
            if (i.getKey(KeyCode::S)) moveDir -= transform->forward;
            if (i.getKey(KeyCode::D)) moveDir += transform->right;
            if (i.getKey(KeyCode::A)) moveDir -= transform->right;

            if (glm::length(moveDir) > 0.0f) {
                pos += glm::normalize(moveDir) * moveSpeed * Time::deltaTime;
            }

            transform->setPosition(pos);
            transform->setEulerAngles(rot);
        }

        if (i.getMouseButtonDown(3)) {
            w.setCursorLock(true);
            //w.setCursorVisibility(false);
        } else if (i.getMouseButtonUp(3)) {
            w.setCursorLock(false);
            //w.setCursorVisibility(true);
        }
    }

    void onTick() override {}
    void afterFrame() override {}
    void onRender() override {}
    void afterTick() override {}
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

    r->mesh = new Mesh(vertices, uvs, normals, indices);
    r->mesh->create();

    Image image = PNG::loadFromFile("res/images/box.png");
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