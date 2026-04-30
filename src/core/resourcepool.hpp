#ifndef SINGULARITY_RESOURCEPOOL_HPP
#define SINGULARITY_RESOURCEPOOL_HPP

#include <core/resourceid.hpp>
#include <unordered_map>

template<typename T>
class ResourcePool {
public:
    ResourcePool() {}
    ~ResourcePool() {}

    std::unordered_map<ResourceID<T>, T*> pool;
    
    T* get(ResourceID<T> id) {
        if (pool.contains(id)) return pool[id];
        return nullptr;
    }

    void set(ResourceID<T> id, T* resource) {
        pool[id] = resource;
    }

    void destroy(ResourceID<T> id) {
        auto it = pool.find(id);
        if (it != pool.end()) {
            pool.erase(it);
        }
    }
};

#endif // SINGULARITY_RESOURCEPOOL_HPP