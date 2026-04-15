#ifndef SINGULARITY_SYSTEMREGISTRY_HPP
#define SINGULARITY_SYSTEMREGISTRY_HPP

#include <vector>

typedef void (*System)();

class SystemRegistry {
public:
    SystemRegistry();
    ~SystemRegistry();

    void update();
    void registerSystem(System system);

private:
    std::vector<System> systems;
};

#endif // SINGULARITY_SYSTEMREGISTRY_HPP