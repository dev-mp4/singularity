#ifndef SINGULARITY_SCENE_HPP
#define SINGULARITY_SCENE_HPP

#include <string>
#include <unordered_map>
#include <core/gameobject.hpp>
#include <core/components/camera.hpp>

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

    void addCamera(Camera* cam);
    void removeCamera(Camera* cam);
    std::vector<Camera*>& getCameras();

private:
    std::unordered_map<std::string, GameObject> scene;
    std::vector<Camera*> cameras;
};

}

#endif