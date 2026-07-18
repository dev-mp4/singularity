#ifndef SINGULARITY_SHADERMANAGER_HPP
#define SINGULARITY_SHADERMANAGER_HPP

#include <core/graphics/shader.hpp>

namespace singularity {

class ShaderManager {
public:
    static Shader* getShader(const std::string& name);
};

}

#endif