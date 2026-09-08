#include "meshrenderer.hpp"
#include <logger/logger.hpp>
#include <core/gameobject.hpp>
#include <core/engine.hpp>

namespace singularity {

void MeshRenderer::onStart() {
    transform = gameObject->getComponent<Transform>();
}

void MeshRenderer::onDestroy() {}
void MeshRenderer::onFrame() {}
void MeshRenderer::onTick() {}
void MeshRenderer::afterFrame() {}

void MeshRenderer::onRender() {
    if (!material || !mesh) {
        Log::error() << "No material or mesh specified in mesh renderer!";
        return;
    }

    if (!transform) {
        Log::error() << "No transform component found!";
        return;
    }

    auto cams = Engine::getInstance()->getScene().getCameras();
    if (cams.size() == 0)
        Log::warn() << "No cameras found!";

    for (auto cam : cams) {
        // direct shader assignment is faster and more clean than setting material parameter
        material->shader->setMat4("vModel", transform->getModelMatrix());
        material->shader->setMat4("vProjView", cam->getProjView());
        material->shader->setVec3("fViewPos", cam->getPos());
        material->use();
        mesh->draw();
    }
}

void MeshRenderer::afterTick() {}

}