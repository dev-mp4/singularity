#include "transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace singularity {

Transform::Transform() : position(0), eulerAngles(0), rotation(glm::identity<glm::quat>()), scale(1),
    forward(0), up(0), right(0) {}

Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale) : position(position), eulerAngles(0), rotation(rotation), scale(scale),
    forward(0), up(0), right(0) {}

Transform::~Transform() {}

void Transform::translate(glm::vec3 direction) {
    position += direction;
}

void Transform::translate(float x, float y, float z) {
    position += glm::vec3(x, y, z);
}

void Transform::rotate(glm::vec3 eulerAngles) {
    glm::quat q(glm::radians(eulerAngles));
    rotation = glm::normalize(rotation * q);
    update();
}

void Transform::rotate(float pitch, float yaw, float roll) {
    glm::quat q(glm::radians(glm::vec3(yaw, pitch, roll)));
    rotation = glm::normalize(rotation * q);
    update();
}

glm::mat4 Transform::getMatrix() {
    glm::mat4 matrix(1.0f);

    matrix = glm::translate(matrix, position);

    glm::mat4 rotMatrix = glm::toMat4(rotation);
    matrix *= rotMatrix;

    matrix = glm::scale(matrix, scale);

    return matrix;
}

void Transform::setPosition(glm::vec3 newPos) {
    position = newPos;
}

void Transform::setEulerAngles(float x, float y, float z) {
    rotation = glm::quat(glm::radians(glm::vec3(y, x, z)));
    eulerAngles = glm::radians(glm::vec3(x, y, z));
    update();
}

void Transform::setRotation(glm::quat newRot) {
    rotation = newRot;
    glm::vec3 yxz = glm::eulerAngles(rotation);
    eulerAngles = glm::radians(glm::vec3(yxz.y, yxz.x, yxz.z));
    update();
}

void Transform::setScale(glm::vec3 newScale) {
    scale = newScale;
}

void Transform::update() {
    forward = glm::normalize(rotation * glm::vec3(0.0f, 0.0f, 1.0f));
    up      = glm::normalize(rotation * glm::vec3(0.0f, 1.0f, 0.0f));
    right   = glm::normalize(rotation * glm::vec3(1.0f, 0.0f, 0.0f));
}

void Transform::onStart() {}
void Transform::onDestroy() {}
void Transform::onFrame() {}
void Transform::onTick() {}
void Transform::afterFrame() {}
void Transform::afterTick() {}

}