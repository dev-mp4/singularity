#include "material.hpp"
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

    for (auto [name, param] : parameters) {
        switch (param.type) {
            case MaterialParameterType::Float:
                shader->setFloat(name, param._float);
                break;
            case MaterialParameterType::Matrix4x4:
                shader->setMat4(name, param._mat4);
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
    parameters[name] = {MaterialParameterType::Matrix4x4, 0, matrix};
}

void Material::setFloat(const std::string& name, float value) {
    parameters[name] = {MaterialParameterType::Float, value, glm::mat4()};
}

}