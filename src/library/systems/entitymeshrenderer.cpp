#include "entitymeshrenderer.hpp"
#include <logger/logger.hpp>
#include <renderer/imesh.hpp>
#include <renderer/itexture.hpp>
#include <renderer/ishader.hpp>
#include <core/engine.hpp>
#include <library/components/camera.hpp>

void entityMeshRenderer(EntityMesh& mesh, Transform& transform) {
    IShader* shader = Engine::getInstance()->resourceManager.get(mesh.shader);
    ITexture* texture = Engine::getInstance()->resourceManager.get(mesh.texture);
    IMesh* _mesh = Engine::getInstance()->resourceManager.get(mesh.mesh);

    if (!shader || !texture || !_mesh) {
        Log::error() << "No shader, texture or mesh specified!";
        return;
    }
    
    Engine::getInstance()->world.query<Camera>().each([&shader, &texture, &_mesh, &transform](Camera& cam) {
        shader->use();
        texture->bind(0);

        glm::mat4 projview = cam.projection * cam.view;
        shader->setUniform("projview", projview);
        shader->setUniform("model", transform.model);

        _mesh->draw();
    });
}