#include "material.hpp"
#include "core/graphics/texture2d.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include <logger/logger.hpp>

namespace singularity {

Material::Material(Shader* shader) : shader(shader) {}
Material::~Material() {}

void Material::use() {
    if (!shader) {
        Log::error() << "No shader specified!";
        return;
    }

    shader->use();

    int nextUnit = 0;

    for (auto [name, param] : parameters) {
        switch (param.type) {
            case MaterialParameterType::Float:
                shader->setFloat(name, param._float);
                break;
            case MaterialParameterType::Matrix4x4:
                shader->setMat4(name, param._mat4);
                break;
            case MaterialParameterType::Texture2D:
                shader->setInt(name, nextUnit);
                param._texture2d.bind(nextUnit);
                nextUnit++;
                break;
            default:
                break;
        }
    }
}

bool Material::compileShader() {
    return shader->compile();
}

void Material::destroy() {
    shader->destroy();
}

void Material::setMat4(const std::string& name, const glm::mat4& matrix) {
    parameters[name] = {MaterialParameterType::Matrix4x4, 0, matrix, Texture2D()};
}

void Material::setFloat(const std::string& name, float value) {
    parameters[name] = {MaterialParameterType::Float, value, glm::mat4(), Texture2D()};
}

void Material::setTexture2D(const std::string& name, Texture2D texture) {
    parameters[name] = {MaterialParameterType::Texture2D, 0, glm::mat4(), texture};
}

}