#ifndef SINGULARITY_TRANSFORM_HPP
#define SINGULARITY_TRANSFORM_HPP

#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>

struct Transform {
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    glm::vec3 eulerAngles;

    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;

    glm::mat4 model;
};

#endif // SINGULARITY_TRANSFORM_HPP