#ifndef SINGULARITY_COMPONENTSTORAGE_HPP
#define SINGULARITY_COMPONENTSTORAGE_HPP

#include <core/ecs/entity.hpp>
#include <cstddef>
#include <optional>
#include <vector>

class ComponentStorageBase {
public:
    virtual ~ComponentStorageBase() = default;

    virtual size_t count() = 0;
    virtual std::vector<Entity>& get_entities() = 0;
    virtual bool has(Entity e) = 0;
};

template<typename T>
class ComponentStorage : public ComponentStorageBase {
public:
    ComponentStorage<T>() {}
    ~ComponentStorage<T>() override {}

    static constexpr size_t INVALID = static_cast<size_t>(-1);

    void insert(Entity e, T data) {
        if (e >= sparse.size())
            sparse.resize(e + 1, INVALID);

        if (sparse[e] != INVALID) {
            dense[sparse[e]] = std::move(data); // overwrite
        } else {
            size_t index = dense.size();
            dense.push_back(std::move(data));
            entities.push_back(e);
            sparse[e] = index;
        }
    }

    std::optional<T> destroy(Entity e) {
        if (!has(e)) return std::nullopt;
        
        size_t index = sparse[e];
        size_t last = dense.size() - 1;

        T removed = std::move(dense[index]);

        if (index != last) {
            dense[index] = std::move(dense[last]);
            Entity moved = entities[last];
            entities[index] = moved;
            sparse[moved] = index;
        }

        dense.pop_back();
        entities.pop_back();
        sparse[e] = INVALID;

        return std::move(removed);
    }

    std::optional<T*> get(Entity e) {
        if (!has(e)) return std::nullopt;

        return &dense[sparse[e]];
    }

    bool has(Entity e) override {
        return e < sparse.size() && sparse[e] != INVALID;
    }

    size_t count() override {
        return entities.size();
    }

    std::vector<Entity>& get_entities() override {
        return entities;
    }

private:
    std::vector<T> dense;
    std::vector<Entity> entities;
    std::vector<size_t> sparse;
};

#endif // SINGULARITY_COMPONENTSTORAGE_HPP