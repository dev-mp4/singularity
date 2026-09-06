#ifndef SINGULARITY_RENDERER_HPP
#define SINGULARITY_RENDERER_HPP

#include <render/itexture2d.hpp>
#include <render/imesh.hpp>
#include <util/types.hpp>
#include <render/features.hpp>
#include <render/irenderer.hpp>
#include <render/ishader.hpp>

namespace singularity {

class Renderer {
public:
    Renderer(RendererType type);
    ~Renderer();

    bool init();
    void destroy();
    void enableBlend();
    void disableBlend();
    void enableCulling();
    void disableCulling();
    void clear(float r, float g, float b);
    RendererFeatures getFeatures();

    RendererType getType();

    IShader* compileShader(const std::string& vertex, const std::string& fragment);
    IMesh* createMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned short>& attributes);
    ITexture2D* createTextureFromImage(Image& image);

private:
    RendererType type;

    IRenderer* renderer;

    RendererFeatures features;

    bool initGL();
};

}

#endif