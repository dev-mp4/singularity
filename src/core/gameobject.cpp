#include "gameobject.hpp"

namespace singularity {

GameObject::GameObject(const std::string& name) : name(name) {}
GameObject::~GameObject() {}

void GameObject::onStart() {
    for (auto& [k, v] : components) {
        v->onStart();
    }
}

void GameObject::onDestroy() {
    for (auto& [k, v] : components) {
        v->onDestroy();
    }
}

void GameObject::onFrame() {
    for (auto& [k, v] : components) {
        v->onFrame();
    }
}

void GameObject::onTick() {
    for (auto& [k, v] : components) {
        v->onTick();
    }
}

void GameObject::afterFrame() {
    for (auto& [k, v] : components) {
        v->afterFrame();
    }
}

void GameObject::afterTick() {
    for (auto& [k, v] : components) {
        v->afterTick();
    }
}

void GameObject::destroy() {
    onDestroy();
    components.clear();
}


}