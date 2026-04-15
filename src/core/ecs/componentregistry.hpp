#ifndef SINGULARITY_COMPONENTREGISTRY_HPP
#define SINGULARITY_COMPONENTREGISTRY_HPP

#include <typeindex>
#include <unordered_map>
#include <core/ecs/componentstorage.hpp>

class ComponentRegistry {
public:
    ComponentRegistry();
    ~ComponentRegistry();

    template<typename T>
    void registerComponent() {
        std::type_index id = typeid(T);

        if (!registry.contains(id)) {
            registry[id] = new ComponentStorage<T>();
        }
    }

    template<typename T>
    ComponentStorageBase* getStorage() {
        std::type_index id = typeid(T);

        if (registry.contains(id)) {
            return registry[id];
        } else {
            return nullptr;
        }
    }

private:
    std::unordered_map<std::type_index, ComponentStorageBase*> registry;
};

#endif // SINGULARITY_COMPONENTREGISTRY_HPP