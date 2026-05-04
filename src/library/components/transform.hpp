#ifndef SINGULARITY_TRANSFORM_HPP
#define SINGULARITY_TRANSFORM_HPP

#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>

namespace singularity {

struct Transform {
    glm::vec3 position = glm::vec3(0);
    glm::quat rotation = glm::quat(1, 0, 0, 0);
    glm::vec3 scale = glm::vec3(1);

    glm::vec3 eulerAngles = glm::vec3(0);

    glm::vec3 forward = glm::vec3(0);
    glm::vec3 up = glm::vec3(0);
    glm::vec3 right = glm::vec3(0);

    glm::mat4 model = glm::mat4(1.0f);
};

}

#endif // SINGULARITY_TRANSFORM_HPP