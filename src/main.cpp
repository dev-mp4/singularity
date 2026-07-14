#include "core/component.hpp"
#include "render/imesh.hpp"
#include "render/ishader.hpp"
#include <SDL3/SDL.h>
#include <window/window.hpp>
#include <util/types.hpp>
#include <render/renderer.hpp>
#include <core/engine.hpp>
#include <util/file.hpp>
#include <core/component.hpp>
#include <core/gameobject.hpp>
#include <logger/logger.hpp>

std::vector<float> vertices = {
    -0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

std::vector<unsigned int> indices = {
    0, 1, 2
};

using namespace singularity;

class MyComp : public Component {
public:
    COMPONENT(MyComp)

    void onStart() {
        Log::info() << "Start!";
    }

    void onDestroy() {
        Log::info() << "Destroy!";
    }

    void onFrame() {
        
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

    IShader* shader = engine.getRenderer().compileShader(readFile("res/shader.vsh"), readFile("res/shader.fsh"));
    if (!shader) {
        return 1;
    }

    IMesh* mesh = engine.getRenderer().createMesh(vertices, indices, {3});
    if (!mesh) {
        return 1;
    }

    GameObject o("Object");

    o.addComponent<MyComp>();

    engine.getScene().addGameObject(std::move(o));

    engine.run();

    shader->destroy();
    mesh->destroy();

    engine.destroy();

    return 0;
}