#include "shader.hpp"
#include <glad/glad.h>

Shader::Shader(unsigned int id) : id(id) {}
Shader::~Shader() {}

void Shader::use() const {
    if (id) glUseProgram(id);
}

std::expected<Shader, std::string> Shader::loadFromGLSL(const std::string& vertex, const std::string& fragment) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    int success;
    char infoLog[512];
    int length;

    // Vertex shader compilation
    const char* vertexShaderCode = vertex.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, &length, infoLog);
        glDeleteShader(vertexShader);
        return std::unexpected(std::string(infoLog, length));
    }

    // Fragment shader compilation
    const char* fragmentShaderCode = fragment.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, &length, infoLog);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return std::unexpected(std::string(infoLog, length));
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, &length, infoLog);
        glDeleteProgram(program);
        return std::unexpected(std::string(infoLog, length));
    }

    return Shader(program);
}

void Shader::destroy() {
    if (id) glDeleteProgram(id); id = 0;
}