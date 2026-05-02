#include "camerasystem.hpp"
#include <core/engine.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/trigonometric.hpp>

void cameraSystem(Camera& camera, Transform& transform) {
    camera.projection = glm::perspective(glm::radians(camera.fov), (float) Engine::getInstance()->window.getWidth() / (float) Engine::getInstance()->window.getHeight(), 0.01f, 100.0f);
    camera.view = glm::inverse(transform.model);
}