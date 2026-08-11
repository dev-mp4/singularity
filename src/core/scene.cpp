#include "scene.hpp"
#include <algorithm>

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

    for (auto& [k, v] : scene) {
        v.onRender();
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
    auto it = scene.find(name);
    if (it != scene.end())
        return &(it->second);
    return nullptr;
}

bool Scene::hasGameObject(const std::string& name) {
    return scene.find(name) != scene.end();
}

void Scene::addCamera(Camera* cam) {
    if (std::find(cameras.begin(), cameras.end(), cam) == cameras.end()) cameras.push_back(cam);
}

void Scene::removeCamera(Camera* cam) {
    auto it = std::find(cameras.begin(), cameras.end(), cam);
    if (it == cameras.end()) return;
    // swap-and-pop
    *it = cameras.back();
    cameras.pop_back();
}

std::vector<Camera*>& Scene::getCameras() {
    return cameras;
}

}