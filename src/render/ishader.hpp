#ifndef SINGULARITY_ISHADER_HPP
#define SINGULARITY_ISHADER_HPP

#include <glm/glm.hpp>
#include <string>

namespace singularity {

class IShader {
public:
    virtual ~IShader() = default;

    virtual bool compileGLSL(const std::string& vertex, const std::string& fragment) = 0;

    virtual void use() = 0;
    virtual void destroy() = 0;
    virtual void setMat4(const std::string& name, const glm::mat4& matrix) = 0;
    virtual void setMat3(const std::string& name, const glm::mat3& matrix) = 0;
    virtual void setFloat(const std::string& name, float value) = 0;
    virtual void setInt(const std::string& name, int value) = 0;
    virtual void setVec3(const std::string& name, const glm::vec3& vector) = 0;
};

}

#endif