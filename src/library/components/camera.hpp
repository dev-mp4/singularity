#ifndef SINGULARITY_CAMERA_HPP
#define SINGULARITY_CAMERA_HPP

#include <glm/glm.hpp>

struct Camera {
    float fov;

    glm::mat4 projection;
    glm::mat4 view;
};

#endif // SINGULARITY_CAMERA_HPP