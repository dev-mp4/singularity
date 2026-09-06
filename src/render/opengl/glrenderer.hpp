#ifndef SINGULARITY_GLRENDERER_HPP
#define SINGULARITY_GLRENDERER_HPP

#include <render/irenderer.hpp>

namespace singularity {

class GLRenderer : public IRenderer {
public:
    GLRenderer();
    ~GLRenderer() override;

    bool init() override;
    void destroy() override;
    void enableBlend() override;
    void disableBlend() override;
    void enableCulling() override;
    void disableCulling() override;    
    void clear(float r, float g, float b) override;
};

}

#endif