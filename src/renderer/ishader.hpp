#ifndef SINGULARITY_ISHADER_HPP
#define SINGULARITY_ISHADER_HPP

#include <glm/glm.hpp>
#include <string>

class IShader {
public:
    virtual ~IShader() = default;

    virtual void use() = 0;
    virtual void destroy() = 0;
    virtual void setUniform(const std::string& name, glm::mat4& matrix) = 0;
};

#endif // SINGULARITY_ISHADER_HPP