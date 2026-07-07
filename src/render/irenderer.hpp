#ifndef SINGULARITY_IRENDERER_HPP
#define SINGULARITY_IRENDERER_HPP

namespace singularity {

class IRenderer {
public:
    virtual ~IRenderer() = default;
    virtual bool init() = 0;
    virtual void destroy() = 0;
    virtual void clear(float r, float g, float b) = 0;
};

}

#endif