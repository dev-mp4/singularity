#include "meshrenderer.hpp"
#include <logger/logger.hpp>
#include <core/gameobject.hpp>

namespace singularity {

void MeshRenderer::onStart() {
    transform = gameObject->getComponent<Transform>();
}

void MeshRenderer::onDestroy() {
    if (material) material->destroy();
    if (mesh) mesh->destroy();
}

void MeshRenderer::onFrame() {
    if (!material || !mesh) {
        Log::error() << "No material or mesh specified in mesh renderer!";
        return;
    }

    if (!transform) {
        Log::error() << "No transform component found!";
        return;
    }

    material->setMat4("vModelMatrix", transform->getMatrix());
    material->use();
    mesh->draw();
}

void MeshRenderer::onTick() {

}

void MeshRenderer::afterFrame() {

}

void MeshRenderer::afterTick() {

}

}