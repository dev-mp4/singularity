#ifndef SINGULARITY_FILE_HPP
#define SINGULARITY_FILE_HPP

#include <string>
#include <fstream>

// Only for internal engine use! not safe!
inline std::string readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        return "";
    }

    std::string contents(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    return contents;
} 

#endif