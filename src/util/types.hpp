#ifndef SINGULARITY_TYPES_HPP
#define SINGULARITY_TYPES_HPP

#include <vector>

namespace singularity {

struct Image {
    int width;
    int height;
    std::vector<unsigned char> data;
};

enum class RendererType {
    OpenGL
};

}

#endif // SINGULARITY_TYPES_HPP