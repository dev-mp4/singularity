#ifndef SINGULARITY_GLTEXTURE2D_HPP
#define SINGULARITY_GLTEXTURE2D_HPP

#include <render/itexture2d.hpp>

namespace singularity {

class GLTexture2D : public ITexture2D {
public:
    GLTexture2D();
    ~GLTexture2D() override;

    void fromImage(Image& image) override;

    void bind(int unit) override;

    void destroy() override;

private:
    int id;
};

}

#endif