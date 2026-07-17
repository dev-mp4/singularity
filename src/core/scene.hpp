#ifndef SINGULARITY_SCENE_HPP
#define SINGULARITY_SCENE_HPP

#include <string>
#include <unordered_map>
#include <core/gameobject.hpp>

namespace singularity {

class Scene {
public:
    Scene();
    ~Scene();
    
    void update();

    void destroy();

    void addGameObject(GameObject&& obj);
    GameObject* getGameObject(const std::string& name);
    bool hasGameObject(const std::string& name);

private:
    std::unordered_map<std::string, GameObject> scene;
};

}

#endif