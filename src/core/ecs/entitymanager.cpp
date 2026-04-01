#include "entitymanager.hpp"
#include <core/ecs/entity.hpp>
#include <algorithm>

EntityManager::EntityManager() : next(1) {}
EntityManager::~EntityManager() {}

Entity EntityManager::create() {
    if (!free.empty()) {
        Entity e = free.back();
        free.pop_back();
        return e;
    } else {
        return next++;
    }
}

void EntityManager::destroy(Entity e) {
    if (exists(e)) {
        free.push_back(e);
    }
}

bool EntityManager::exists(Entity e) {
    return std::find(free.begin(), free.end(), e) == free.end() && e < next && e != INVALID_ENTITY;
}