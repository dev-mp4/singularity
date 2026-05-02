#ifndef SINGULARITY_ENTITYMESH_HPP
#define SINGULARITY_ENTITYMESH_HPP

#include <core/resourceid.hpp>
#include <renderer/ishader.hpp>
#include <renderer/itexture.hpp>
#include <renderer/imesh.hpp>

struct EntityMesh {
    ResourceID<IShader>  shader;
    ResourceID<ITexture> texture;
    ResourceID<IMesh>    mesh;
};

#endif // SINGULARITY_ENTITYMESH_HPP