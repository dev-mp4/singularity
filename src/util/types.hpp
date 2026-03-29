#ifndef SINGULARITY_TYPES_HPP
#define SINGULARITY_TYPES_HPP

#include <vector>

struct Image {
    int width;
    int height;
    std::vector<unsigned char> data;
};

#endif // SINGULARITY_TYPES_HPP