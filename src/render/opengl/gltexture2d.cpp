#include "gltexture2d.hpp"
#include <logger/logger.hpp>
#include <cmath>
#include <glad/glad.h>

namespace singularity {

GLTexture2D::GLTexture2D() : id(0) {}
GLTexture2D::~GLTexture2D() {}

static int filterToValue(FilteringMode mode, bool mipmap) {
    switch (mode) {
        case FilteringMode::Pixel:
            return mipmap ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST;
        case FilteringMode::Bilinear:
            return mipmap ? GL_LINEAR_MIPMAP_NEAREST : GL_LINEAR;
        case FilteringMode::Trilinear:
            return mipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR;
    }
}

static int wrapToValue(WrapMode mode) {
    switch (mode) {
        case WrapMode::Repeat:
            return GL_REPEAT;
        case WrapMode::ClampToEdge:
            return GL_CLAMP_TO_EDGE;
        case WrapMode::Mirror:
            return GL_MIRRORED_REPEAT;
    }
}

bool GLTexture2D::fromImage(Image& image) {
    if (image.width == 0 || image.height == 0) return false;

    int min = filterToValue(filter, true);
    int mag = filterToValue(filter, false);

    int wrap = wrapToValue(wrapMode);

    GLuint tex;
    glCreateTextures(GL_TEXTURE_2D, 1, &tex);

    GLuint levels = mipmaps
    ? 1 + static_cast<GLuint>(std::floor(std::log2(std::max(image.width, image.height))))
    : 1;

    glTextureStorage2D(tex, levels, GL_RGBA8, image.width, image.height);

    glTextureParameteri(tex, GL_TEXTURE_WRAP_S, wrap);
    glTextureParameteri(tex, GL_TEXTURE_WRAP_T, wrap);

    glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, min);
    glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, mag);

    glTextureSubImage2D(
        tex, 
        0,
        0, 0,
        image.width, image.height, 
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        image.data.data()
    );

    glGenerateTextureMipmap(tex);

    id = tex;
    return true;
}

void GLTexture2D::bind(int unit) {
    if (id) glBindTextureUnit(unit, id);;
}

void GLTexture2D::destroy() {
    if (id) glDeleteTextures(1, (GLuint*)&id);
}

}