#ifndef SINGULARITY_CAMERA_HPP
#define SINGULARITY_CAMERA_HPP

#include <glm/glm.hpp>

namespace singularity {

struct Camera {
    float fov = 60.0f;

    glm::mat4 projection;
    glm::mat4 view;
};

}

#endif // SINGULARITY_CAMERA_HPP