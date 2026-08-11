#ifndef SINGULARITY_GAMEOBJECT_HPP
#define SINGULARITY_GAMEOBJECT_HPP

#include <string>
#include <unordered_map>
#include <core/component.hpp>
#include <logger/logger.hpp>

namespace singularity {

class GameObject {
public:
    GameObject(const std::string& name);
    ~GameObject();

    std::string name;

    template <typename T>
    T* getComponent() {
        auto it = components.find(T::_getName());

        if (it == components.end())
            return nullptr;

        return static_cast<T*>(it->second);
    }

    template <typename T>
    T* addComponent() {
        if (components.find(T::_getName()) != components.end()) return nullptr;
        components.try_emplace(T::_getName(), new T());
        components[T::_getName()]->gameObject = this;
        return static_cast<T*>(components[T::_getName()]);
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
    void onRender();
    void afterTick();

    void destroy();

private:
    std::unordered_map<std::string_view, Component*> components;
};

}

#endif