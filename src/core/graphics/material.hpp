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
    Matrix3x3,
    Texture2D,
    Vector3
};

struct MaterialParameter {
    MaterialParameterType type;
    float _float;
    glm::mat4 _mat4;
    glm::mat3 _mat3;
    Texture2D _texture2d;
    glm::vec3 _vec3;
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
    void setMat3(const std::string& name, const glm::mat3& matrix);
    void setFloat(const std::string& name, float value);
    void setTexture2D(const std::string& name, Texture2D texture);
    void setVec3(const std::string& name, const glm::vec3& vector);

private:
    std::unordered_map<std::string, MaterialParameter> parameters;
};

}

#endif