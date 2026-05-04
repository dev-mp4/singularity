#include "transformsystem.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace singularity {

void transformSystem(Transform& transform) {
    glm::vec3 yzx = glm::eulerAngles(transform.rotation);

    transform.eulerAngles = glm::vec3(yzx.z, yzx.x, yzx.y);

    transform.forward = glm::normalize(transform.rotation * glm::vec3(0, 0, -1));
    transform.up      = glm::normalize(transform.rotation * glm::vec3(0, 1,  0));
    transform.right   = glm::normalize(transform.rotation * glm::vec3(1, 0,  0));

    transform.model = glm::mat4(1.0);
    transform.model = glm::translate(transform.model, transform.position);

    glm::mat4 rotMatrix = glm::toMat4(transform.rotation);
    transform.model *= rotMatrix;

    transform.model = glm::scale(transform.model, transform.scale);
}

}