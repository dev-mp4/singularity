#include "shader.hpp"
#include <core/engine.hpp>
#include <logger/logger.hpp>

namespace singularity {

Shader::Shader(const std::string& vertex, const std::string& fragment) : vertex(vertex), fragment(fragment), shader(nullptr) {}
Shader::~Shader() {}

bool Shader::compile() {
    if (Engine::getInstance() == nullptr) {
        Log::error() << "No engine instance!";
        return false;
    }

    shader = Engine::getInstance()->getRenderer().createShader();
    if (!shader) return false;
    return shader->compileGLSL(vertex, fragment);
}

void Shader::use() {
    if (shader) shader->use();
}

void Shader::destroy() {
    if (shader) shader->destroy();
}

void Shader::setMat4(const std::string& name, const glm::mat4& matrix) {
    if (shader) shader->setMat4(name, matrix);
}

void Shader::setMat3(const std::string& name, const glm::mat3& matrix) {
    if (shader) shader->setMat3(name, matrix);
}

void Shader::setFloat(const std::string& name, float value) {
    if (shader) shader->setFloat(name, value);
}

void Shader::setInt(const std::string& name, int value) {
    if (shader) shader->setInt(name, value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& vector) {
    if (shader) shader->setVec3(name, vector);
}

}