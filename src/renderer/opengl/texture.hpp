#ifndef SINGULARITY_TEXTURE_HPP
#define SINGULARITY_TEXTURE_HPP

#include <util/types.hpp>
#include <renderer/itexture.hpp>

namespace singularity {

class Texture : public ITexture {
public:
    Texture(unsigned int id);
    ~Texture() override;

    void bind(int index) override;
    void destroy() override;
    static Texture* loadFromImage(Image* image);

private:
    unsigned int id;
};

}

#endif // SINGULARITY_TEXTURE_HPP