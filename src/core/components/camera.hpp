#ifndef SINGULARITY_CAMERA_HPP
#define SINGULARITY_CAMERA_HPP

#include <core/component.hpp>
#include <core/components/transform.hpp>
#include <glm/glm.hpp>

namespace singularity {

class Camera : public Component {
    COMPONENT(Camera)

public:
    void onStart() override;
    void onDestroy() override;
    void onFrame() override;
    void onTick() override;
    void afterFrame() override;
    void onRender() override;
    void afterTick() override;

    glm::mat4 getProjView();
    glm::vec3 getPos();

    void setFOV(float fov);
    void setClipping(float near, float far);

    float fov = 60.0f;
    float near = 0.1f;
    float far = 100.0f;

private:
    glm::mat4 proj;
    bool dirty = false;
    float oldAspect = 0.0f;

    Transform* t;
};

}

#endif