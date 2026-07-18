#ifndef SINGULARITY_MESHRENDERER_HPP
#define SINGULARITY_MESHRENDERER_HPP

#include <core/component.hpp>
#include <core/graphics/mesh.hpp>
#include <core/material.hpp>
#include <core/components/transform.hpp>

namespace singularity {

class MeshRenderer : public Component {
    COMPONENT(MeshRenderer)

public:
    Mesh* mesh;
    
    Material* material;

    Transform* transform;

    void onStart() override;

    void onDestroy() override;

    void onFrame() override;

    void onTick() override;

    void afterFrame() override;

    void afterTick() override;
};

}

#endif