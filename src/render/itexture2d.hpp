#ifndef SINGULARITY_ITEXTURE2D_HPP
#define SINGULARITY_ITEXTURE2D_HPP

#include <util/types.hpp>

namespace singularity {

class ITexture2D {
public:
    virtual ~ITexture2D() = default;

    virtual void fromImage(Image& image) = 0;

    virtual void bind(int unit) = 0;

    virtual void destroy() = 0;

    bool mipmaps;
    WrapMode wrapMode;
    FilteringMode filter;
};

}

#endif