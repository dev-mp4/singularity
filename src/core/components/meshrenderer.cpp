#include "meshrenderer.hpp"
#include <logger/logger.hpp>
#include <core/gameobject.hpp>

namespace singularity {

void MeshRenderer::onStart() {
    transform = gameObject->getComponent<Transform>();
}

void MeshRenderer::onDestroy() {
    if (shader) shader->destroy();
    if (mesh) mesh->destroy();
}

void MeshRenderer::onFrame() {
    if (!shader || !mesh) {
        Log::error() << "No shader or mesh specified in mesh renderer!";
        return;
    }

    if (!transform) {
        Log::error() << "No transform component found!";
        return;
    }

    shader->use();
    shader->setMat4("vModelMatrix", transform->getMatrix());
    mesh->draw();
}

void MeshRenderer::onTick() {

}

void MeshRenderer::afterFrame() {

}

void MeshRenderer::afterTick() {

}

}