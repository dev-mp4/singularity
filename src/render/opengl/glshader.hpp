#ifndef SINGULARITY_GLSHADER_HPP
#define SINGULARITY_GLSHADER_HPP

#include <render/ishader.hpp>

namespace singularity {

class GLShader : public IShader {
public:
    GLShader();
    ~GLShader() override;

    bool compileGLSL(const std::string& vertex, const std::string& fragment) override;

    void use() override;
    void destroy() override;

    void setMat4(const std::string& name, const glm::mat4& matrix) override;
    void setFloat(const std::string& name, float value) override;
    void setInt(const std::string& name, int value) override;

private:
    unsigned int id;
};

}

#endif