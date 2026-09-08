#include "texture2d.hpp"
#include <core/engine.hpp>

namespace singularity {

Texture2D::Texture2D() : texture(nullptr) {}
Texture2D::~Texture2D() {}

bool Texture2D::fromImage(Image& image) {
    if (Engine::getInstance() == nullptr) {
        Log::error() << "No engine instance!";
        return false;
    }

    texture = Engine::getInstance()->getRenderer().createTexture2D();
    if (!texture) return false;
    texture->mipmaps = mipmaps;
    texture->wrapMode = wrapMode;
    texture->filter = filter;
    return texture->fromImage(image);
}

void Texture2D::bind(int unit) {
    if (texture) texture->bind(unit);
}

void Texture2D::destroy() {
    if (texture) texture->destroy();
}

}