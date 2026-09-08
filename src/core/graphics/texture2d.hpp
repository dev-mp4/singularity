#ifndef SINGULARITY_TEXTURE2D_HPP
#define SINGULARITY_TEXTURE2D_HPP

#include <util/types.hpp>
#include <render/itexture2d.hpp>

namespace singularity {

class Texture2D {
public:
    Texture2D();
    ~Texture2D();

    bool fromImage(Image& image);

    void bind(int unit);

    void destroy();

    bool mipmaps = true;
    WrapMode wrapMode = WrapMode::ClampToEdge;
    FilteringMode filter = FilteringMode::Bilinear;

private:
    ITexture2D* texture;
};

}

#endif