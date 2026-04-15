#ifndef SINGULARITY_SCENE_HPP
#define SINGULARITY_SCENE_HPP

#include <core/ecs/systemregistry.hpp>
#include <core/ecs/componentregistry.hpp>
#include <core/ecs/entitymanager.hpp>

class Scene {
public:
    Scene();
    Scene(ComponentRegistry componentRegistry, SystemRegistry systemRegistry, EntityManager manager);
    ~Scene();

    ComponentRegistry& getComponentRegistry();
    SystemRegistry& getSystemRegistry();
    EntityManager& getEntityManager();

private:
    ComponentRegistry componentRegistry;
    SystemRegistry systemRegistry;
    EntityManager manager;
};

#endif // SINGULARITY_SCENE_HPP