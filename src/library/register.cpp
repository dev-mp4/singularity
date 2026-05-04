#include "register.hpp"
#include <core/engine.hpp>
#include <logger/logger.hpp>
#include <renderer/ishader.hpp>
#include <renderer/itexture.hpp>
#include <renderer/imesh.hpp>
#include <library/systems/camerasystem.hpp>
#include <library/systems/transformsystem.hpp>
#include <library/systems/entitymeshrenderer.hpp>

namespace singularity {

void Library::registerAll() {
    Engine* engine = Engine::getInstance();

    if (!engine) {
        Log::error() << "Cannot register library: no engine instance found!";
        return;
    }

    engine->resourceManager.registerResource<IShader>();
    engine->resourceManager.registerResource<ITexture>();
    engine->resourceManager.registerResource<IMesh>();

    engine->world.system<Transform>().kind(Engine::PostUpdate).each(transformSystem);
    engine->world.system<Camera, Transform>().kind(Engine::PostUpdate).each(cameraSystem);
    engine->world.system<EntityMesh, Transform>().kind(Engine::Render).each(entityMeshRenderer);
}

}