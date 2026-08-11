#include "camera.hpp"
#include "glm/trigonometric.hpp"
#include <core/engine.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace singularity {

void Camera::onStart() {
    Window& window = Engine::getInstance()->getWindow();
    float aspect = (float)window.width / (float)window.height;
    oldAspect = aspect;
    proj = glm::perspective(glm::radians(fov), aspect, near, far);

    Engine::getInstance()->getScene().addCamera(this);

    t = gameObject->getComponent<Transform>();
    if (!t) {
        Log::error() << "No transform found on camera!";
    }
}

void Camera::onDestroy() {
    Engine::getInstance()->getScene().removeCamera(this);
}

void Camera::onFrame() {}

void Camera::onTick() {}

void Camera::afterFrame() {
    Window& window = Engine::getInstance()->getWindow();
    float aspect = (float)window.width / (float)window.height;
    if (aspect != oldAspect)
        dirty = true;
    oldAspect = aspect;

    if (dirty)
        proj = glm::perspective(glm::radians(fov), aspect, near, far);
}

void Camera::onRender() {}

void Camera::afterTick() {}

glm::mat4 Camera::getProjView() {
    if (!t)
        return glm::mat4(1.0f);

    return proj * glm::inverse(t->getMatrix());
}

void Camera::setFOV(float fov) {
    this->fov = fov;
    dirty = true;
}

void Camera::setClipping(float near, float far) {
    this->near = near;
    this->far = far;
    dirty = true;
}

}