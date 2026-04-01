#ifndef SINGULARITY_ENTITYMANAGER_HPP
#define SINGULARITY_ENTITYMANAGER_HPP

#include <core/ecs/entity.hpp>
#include <vector>

class EntityManager {
public:
    EntityManager();
    ~EntityManager();

    Entity create();
    void destroy(Entity e);
    bool exists(Entity e);

private:
    Entity next;
    std::vector<Entity> free;
};

#endif // SINGULARITY_ENTITYMANAGER_HPP