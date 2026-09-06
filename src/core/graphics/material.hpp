#ifndef SINGULARITY_MATERIAL_HPP
#define SINGULARITY_MATERIAL_HPP

#include <core/graphics/shader.hpp>
#include <core/graphics/texture2d.hpp>
#include <glm/glm.hpp>
#include <unordered_map>

namespace singularity {

enum class MaterialParameterType {
    Float,
    Matrix4x4,
    Texture2D
};

struct MaterialParameter {
    MaterialParameterType type;
    float _float;
    glm::mat4 _mat4;
    Texture2D _texture2d;
};

class Material {
public:
    Material(Shader* shader);
    ~Material();

    Shader* shader;

    void use();
    bool compileShader();
    void destroy();

    void setMat4(const std::string& name, const glm::mat4& matrix);
    void setFloat(const std::string& name, float value);
    void setTexture2D(const std::string& name, Texture2D texture);

private:
    std::unordered_map<std::string, MaterialParameter> parameters;
};

}

#endif