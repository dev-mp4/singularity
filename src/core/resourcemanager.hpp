#ifndef SINGULARITY_RESOURCEMANAGER_HPP
#define SINGULARITY_RESOURCEMANAGER_HPP

#include <any>
#include <cstddef>
#include <memory>
#include <typeindex>
#include <vector>
#include <algorithm>
#include <core/resourceid.hpp>
#include <core/resourcepool.hpp>

class ResourceManager {
public:
    ResourceManager() {}
    ~ResourceManager() {}

    template<typename T>
    T* get(ResourceID<T> id) {
        auto poolResult = get_pool<T>();
        if (poolResult != nullptr) {
            return poolResult->get(id);
        }
        return nullptr;
    }

    template<typename T>
    void registerResource() {
        if (!pools.contains(typeid(T))) {
            pools[typeid(T)] = new ResourcePool<T>();
        }
    }

    template<typename T>
    ResourceID<T> add(T* resource) {
        if (get_pool<T>() == nullptr) return ResourceID<T> {.id=0};

        ResourceID<T> id = {.id=getNextID()};
        
        get_pool<T>()->set(id, std::unique_ptr<T>(resource));

        return id;
    }

    template<typename T>
    void destroy(ResourceID<T> id) {
        if (get_pool<T>() == nullptr) return;

        get_pool<T>()->destroy(id);

        destroyID(id.id);
    }

    bool isValid(std::size_t id) {
        return std::find(free.begin(), free.end(), id) == free.end() && id < next && id != 0;
    }

    void destroy() {
        for (auto& [k, v] : pools) {
            v->destroy();
        }
        next = 1;
        free.clear();
    }
private:
    std::unordered_map<std::type_index, IResourcePool*> pools;

    template<typename T>
    ResourcePool<T>* get_pool() {
        if (pools.contains(typeid(T))) return static_cast<ResourcePool<T>*>(pools[typeid(T)]);
        return nullptr;
    }

    std::size_t next = 1;
    std::vector<std::size_t> free;

    std::size_t getNextID() {
        if (!free.empty()) {
            std::size_t id = free.back();
            free.pop_back();
            return id;
        } else {
            return next++;
        }
    }

    void destroyID(std::size_t id) {
        if (isValid(id)) free.push_back(id);
    }
};

#endif // SINGULARITY_RESOURCEMANAGER_HPP