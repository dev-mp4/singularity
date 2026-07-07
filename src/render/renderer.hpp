#ifndef SINGULARITY_RENDERER_HPP
#define SINGULARITY_RENDERER_HPP

#include <util/types.hpp>
#include <render/irenderer.hpp>

namespace singularity {

class Renderer {
public:
    Renderer(RendererType type);
    ~Renderer();

    bool init();
    void destroy();
    void clear(float r, float g, float b);

private:
    RendererType type;

    IRenderer* renderer;

    bool initGL();
};

}

#endif