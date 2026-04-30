#ifndef SINGULARITY_RESOURCEPOOL_HPP
#define SINGULARITY_RESOURCEPOOL_HPP

#include <core/resourceid.hpp>
#include <unordered_map>
#include <memory>

struct IResourcePool {
public:
    virtual ~IResourcePool() = default;
    virtual void destroy() = 0;
};

template<typename T>
class ResourcePool : public IResourcePool {
public:
    ResourcePool() {}
    ~ResourcePool() override {}

    std::unordered_map<ResourceID<T>, std::unique_ptr<T>> pool;
    
    T* get(ResourceID<T> id) {
        if (pool.contains(id)) return pool[id].get();
        return nullptr;
    }

    void set(ResourceID<T> id, std::unique_ptr<T> resource) {
        pool[id] = std::move(resource);
    }

    void destroy(ResourceID<T> id) {
        auto it = pool.find(id);
        if (it != pool.end()) {
            pool.erase(it);
        }
    }

    void destroy() override {
        for (auto& [k, v] : pool) {
            v->destroy();
        }
        pool.clear();
    }
};

#endif // SINGULARITY_RESOURCEPOOL_HPP