#ifndef SINGULARITY_PNG_HPP
#define SINGULARITY_PNG_HPP

#include <string>
#include <expected>
#include <util/types.hpp>
#include <util/result.hpp>

namespace PNG {
    Result<Image> loadFromFile(const std::string& filename);
}

#endif // SINGULARITY_PNG_HPP