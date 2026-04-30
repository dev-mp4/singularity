#include "png.hpp"
#include <iostream>
#include <spng.h>
#include <fstream>

Image* PNG::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Failed to open " << filename << std::endl;
        return nullptr;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<unsigned char> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        std::cerr << "Failed to read " << filename << std::endl;
        return nullptr;
    }

    spng_ctx* ctx = spng_ctx_new(0);
    if (!ctx) {
        std::cerr << "Failed to create context" << std::endl;
        return nullptr;
    }

    int ret = spng_set_png_buffer(ctx, buffer.data(), buffer.size());;
    if (ret) {
        spng_ctx_free(ctx);
        std::cerr << "Failed to set PNG buffer: " << spng_strerror(ret) << std::endl;
        return nullptr;
    }

    spng_ihdr ihdr{};
    ret = spng_get_ihdr(ctx, &ihdr);
    if (ret) {
        spng_ctx_free(ctx);
        std::cerr << "Failed to read PNG header: " << spng_strerror(ret) << std::endl;
        return nullptr;
    }

    int width = ihdr.width;
    int height = ihdr.height;

    size_t out_size = 0;
    ret = spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &out_size);
    if (ret) {
        spng_ctx_free(ctx);
        std::cerr << "Failed to get image size: " << spng_strerror(ret) << std::endl;
        return nullptr;
    }

    std::vector<unsigned char> pixels(out_size);
    ret = spng_decode_image(ctx, pixels.data(), out_size, SPNG_FMT_RGBA8, 0);
    if (ret) {
        spng_ctx_free(ctx);
        std::cerr << "Failed to decode PNG image: " << spng_strerror(ret) << std::endl;
        return nullptr;
    }

    return new Image {width, height, std::move(pixels)};
}