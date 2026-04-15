#include "systemregistry.hpp"

SystemRegistry::SystemRegistry() {}
SystemRegistry::~SystemRegistry() {}

void SystemRegistry::update() {
    for (auto system : systems) {
        system();
    }
}

void SystemRegistry::registerSystem(System system) {
    systems.push_back(system);
}