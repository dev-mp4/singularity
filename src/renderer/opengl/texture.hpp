#ifndef SINGULARITY_TEXTURE_HPP
#define SINGULARITY_TEXTURE_HPP

#include <util/result.hpp>
#include <util/types.hpp>
#include <renderer/itexture.hpp>

class Texture : public ITexture {
public:
    Texture(unsigned int id);
    ~Texture() override;

    void bind(int index) override;
    void destroy() override;
    static Result<Texture> loadFromImage(Image data);

private:
    unsigned int id;
};

#endif // SINGULARITY_TEXTURE_HPP