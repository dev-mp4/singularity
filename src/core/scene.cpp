#include "scene.hpp"
#include "core/ecs/componentregistry.hpp"
#include "core/ecs/systemregistry.hpp"

Scene::Scene() {}
Scene::Scene(ComponentRegistry componentRegistry, SystemRegistry systemRegistry, EntityManager manager) : componentRegistry(componentRegistry), systemRegistry(systemRegistry), manager(manager) {}
Scene::~Scene() {}

ComponentRegistry& Scene::getComponentRegistry() {
    return componentRegistry;
}

SystemRegistry& Scene::getSystemRegistry() {
    return systemRegistry;
}

EntityManager& Scene::getEntityManager() {
    return manager;
}
