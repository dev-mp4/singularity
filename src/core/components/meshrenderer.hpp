#ifndef SINGULARITY_MESHRENDERER_HPP
#define SINGULARITY_MESHRENDERER_HPP

#include <core/component.hpp>
#include <core/graphics/mesh.hpp>
#include <core/graphics/material.hpp>
#include <core/components/transform.hpp>

namespace singularity {

class MeshRenderer : public Component {
    COMPONENT(MeshRenderer)

public:
    Mesh* mesh = nullptr;
    Material* material = nullptr;
    Transform* transform = nullptr;

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