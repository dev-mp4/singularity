#ifndef SINGULARITY_TEXTURE_HPP
#define SINGULARITY_TEXTURE_HPP

#include <expected>
#include <string>
#include <util/types.hpp>

class Texture {
public:
    Texture(unsigned int id);
    ~Texture();

    void bind(int x);
    void destroy();
    static std::expected<Texture, std::string> loadFromImage(Image data);

private:
    unsigned int id;
};

#endif // SINGULARITY_TEXTURE_HPP