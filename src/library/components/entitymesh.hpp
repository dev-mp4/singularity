#ifndef SINGULARITY_ENTITYMESH_HPP
#define SINGULARITY_ENTITYMESH_HPP

#include <core/resourceid.hpp>
#include <renderer/ishader.hpp>
#include <renderer/itexture.hpp>
#include <renderer/imesh.hpp>

namespace singularity {

struct EntityMesh {
    ResourceID<IShader>  shader = ResourceID<IShader>{0};
    ResourceID<ITexture> texture = ResourceID<ITexture>{0};
    ResourceID<IMesh>    mesh = ResourceID<IMesh>{0};
};

}

#endif // SINGULARITY_ENTITYMESH_HPP