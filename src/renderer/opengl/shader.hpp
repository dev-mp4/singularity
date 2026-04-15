#ifndef SINGULARITY_SHADER_HPP
#define SINGULARITY_SHADER_HPP

#include <util/result.hpp>
#include <string>
#include <renderer/ishader.hpp>

class Shader : public IShader {
public:
    Shader(unsigned int id);
    ~Shader() override;

    void use() override;
    void destroy() override;
    static Result<Shader> loadFromGLSL(const std::string& vertex, const std::string& fragment);

private:
    unsigned int id;
};

#endif //SINGULARITY_SHADER_HPP