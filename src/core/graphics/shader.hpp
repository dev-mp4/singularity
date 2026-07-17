#ifndef SINGULARITY_SHADER_HPP
#define SINGULARITY_SHADER_HPP

#include <string>
#include <render/ishader.hpp>
#include <glm/glm.hpp>

namespace singularity {

class Shader {
public:
    Shader(const std::string& vertex, const std::string& fragment);
    ~Shader();

    bool compile();
    void use();
    void destroy();

    void setMat4(const std::string& name, const glm::mat4& matrix);

private:
    std::string vertex;
    std::string fragment;

    IShader* shader;
};

}

#endif