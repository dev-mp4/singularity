#ifndef SINGULARITY_ITEXTURE_HPP
#define SINGULARITY_ITEXTURE_HPP

namespace singularity {

class ITexture {
public:
    virtual ~ITexture() = default;

    virtual void bind(int index) = 0;
    virtual void destroy() = 0;
};

}

#endif // SINGULARITY_ITEXTURE_HPP