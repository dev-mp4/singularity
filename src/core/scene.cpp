#include "scene.hpp"

namespace singularity {

Scene::Scene() {}
Scene::~Scene() {}

void Scene::update() {
    for (auto& [k, v] : scene) {
        v.onFrame();
    }

    for (auto& [k, v] : scene) {
        v.afterFrame();
    }
}

void Scene::destroy() {
    for (auto& [k, v] : scene) {
        v.onDestroy();
    }
    scene.clear();
}

void Scene::addGameObject(GameObject&& obj) {
    if (scene.find(obj.name) == scene.end()) {
        std::string name = obj.name; // Keep a copy of the key
        scene.try_emplace(name, std::move(obj));
        scene.at(name).onStart();
    }
}

GameObject* Scene::getGameObject(const std::string& name) {
    Log::info() << scene.size();
    for (auto& [k, v] : scene) {
        Log::info() << k;
    }

    auto it = scene.find(name);
    if (it != scene.end())
        return &(it->second);
    return nullptr;
}

bool Scene::hasGameObject(const std::string& name) {
    return scene.find(name) != scene.end();
}

}