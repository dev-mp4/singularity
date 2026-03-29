#include "png.hpp"
#include <spng.h>
#include <fstream>

std::expected<Image, std::string> PNG::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        return std::unexpected("Failed to open " + filename);
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<unsigned char> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        return std::unexpected("Failed to read " + filename);
    }

    spng_ctx* ctx = spng_ctx_new(0);
    if (!ctx) {
        return std::unexpected("Failed to create context");
    }

    int ret = spng_set_png_buffer(ctx, buffer.data(), buffer.size());;
    if (ret) {
        spng_ctx_free(ctx);
        return std::unexpected("Failed to set PNG buffer: " + std::string(spng_strerror(ret)));
    }

    spng_ihdr ihdr{};
    ret = spng_get_ihdr(ctx, &ihdr);
    if (ret) {
        spng_ctx_free(ctx);
        return std::unexpected("Failed to read PNG header: " + std::string(spng_strerror(ret)));
    }

    int width = ihdr.width;
    int height = ihdr.height;

    size_t out_size = 0;
    ret = spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &out_size);
    if (ret) {
        spng_ctx_free(ctx);
        return std::unexpected("Failed to get PNG image size: " + std::string(spng_strerror(ret)));
    }

    std::vector<unsigned char> pixels(out_size);
    ret = spng_decode_image(ctx, pixels.data(), out_size, SPNG_FMT_RGBA8, 0);
    if (ret) {
        spng_ctx_free(ctx);
        return std::unexpected("Failed to decode PNG image: " + std::string(spng_strerror(ret)));
    }

    return Image {width, height, std::move(pixels)};
}