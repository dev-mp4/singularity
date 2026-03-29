#ifndef SINGULARITY_PNG_HPP
#define SINGULARITY_PNG_HPP

#include <string>
#include <expected>
#include <util/types.hpp>

namespace PNG {
    std::expected<Image, std::string> loadFromFile(const std::string& filename);
}

#endif // SINGULARITY_PNG_HPP