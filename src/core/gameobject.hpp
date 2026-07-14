#ifndef SINGULARITY_GAMEOBJECT_HPP
#define SINGULARITY_GAMEOBJECT_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include <core/component.hpp>

namespace singularity {

class GameObject {
public:
    GameObject(const std::string& name);
    ~GameObject();

    // Make GameObject move-only
    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject&) = delete;

    GameObject(GameObject&&) noexcept = default;
    GameObject& operator=(GameObject&&) noexcept = default;

    std::string name;

    template <typename T>
    Component* getComponent() {
        if (components.find(T::_getName()) == components.end()) return nullptr;
        auto it = components.find(T::_getName());

        if (it == components.end())
            return nullptr;

        return static_cast<T*>(it->second.get());
    }

    template <typename T>
    T* addComponent() {
        if (components.find(T::_getName()) != components.end()) return nullptr;
        components[T::_getName()] = std::make_unique<T>();
        components[T::_getName()]->gameObject = this;
        return static_cast<T*>(components[T::_getName()].get());
    }

    template <typename T>
    bool hasComponent() {
        return components.find(T::_getName()) != components.end();
    }

    void onStart();
    void onDestroy();
    void onFrame();
    void onTick();
    void afterFrame();
    void afterTick();

    void destroy();

private:
    std::unordered_map<std::string_view, std::unique_ptr<Component>> components;
};

}

#endif