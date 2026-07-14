#ifndef SINGULARITY_COMPONENT_HPP
#define SINGULARITY_COMPONENT_HPP

namespace singularity {

class GameObject;

#define COMPONENT(name) \
    static constexpr std::string_view _getName() { return #name; }

class Component {
public:
    virtual ~Component() = default;

    GameObject* gameObject;

    virtual void onStart() = 0;
    virtual void onDestroy() = 0;
    virtual void onFrame() = 0;
    virtual void onTick() = 0;
    virtual void afterFrame() = 0;
    virtual void afterTick() = 0;
};

}

#endif