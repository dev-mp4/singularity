#ifndef SINGULARITY_SHADER_HPP
#define SINGULARITY_SHADER_HPP

#include <string>
#include <expected>

class Shader {
public:
    Shader(unsigned int id);
    ~Shader();

    void use();
    void destroy();
    static std::expected<Shader, std::string> loadFromGLSL(const std::string& vertex, const std::string& fragment);

private:
    unsigned int id;
};

#endif //SINGULARITY_SHADER_HPP