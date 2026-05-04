#ifndef SINGULARITY_SHADER_HPP
#define SINGULARITY_SHADER_HPP

#include <string>
#include <renderer/ishader.hpp>

namespace singularity {

class Shader : public IShader {
public:
    Shader(unsigned int id);
    ~Shader() override;

    void use() override;
    void destroy() override;
    static Shader* loadFromGLSL(const std::string& vertex, const std::string& fragment);
    void setUniform(const std::string& name, glm::mat4& matrix) override;

private:
    unsigned int id;
};

}

#endif //SINGULARITY_SHADER_HPP