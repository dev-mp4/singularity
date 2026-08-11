#ifndef SINGULARITY_TRANSFORM_HPP
#define SINGULARITY_TRANSFORM_HPP

#include <core/component.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace singularity {

class Transform : public Component {
    COMPONENT(Transform)

public:
    Transform();
    Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);
    ~Transform();

    void translate(glm::vec3 direction);
    void translate(float x, float y, float z);

    void rotate(glm::vec3 eulerAngles);
    void rotate(float pitch, float yaw, float roll);

    void resize(glm::vec3 scale);
    void resize(float x, float y, float z);

    void setPosition(glm::vec3 newPos);

    void setEulerAngles(float x, float y, float z);
    void setRotation(glm::quat newRot);
    
    void setScale(glm::vec3 newScale);

    glm::mat4 getMatrix();

    void update();

    glm::vec3 position;
    glm::vec3 eulerAngles;
    glm::quat rotation;
    glm::vec3 scale;

    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;

    void onStart() override;
    void onDestroy() override;
    void onFrame() override;
    void onTick() override;
    void afterFrame() override;
    void onRender() override;
    void afterTick() override;
};

}

#endif