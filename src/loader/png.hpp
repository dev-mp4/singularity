#ifndef SINGULARITY_PNG_HPP
#define SINGULARITY_PNG_HPP

#include <string>
#include <util/types.hpp>

namespace PNG {
    Image* loadFromFile(const std::string& filename);
}

#endif // SINGULARITY_PNG_HPP