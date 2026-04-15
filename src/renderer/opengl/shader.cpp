#include "shader.hpp"
#include <glad/glad.h>
#include <util/result.hpp>

Shader::Shader(unsigned int id) : id(id) {}
Shader::~Shader() {}

void Shader::use() {
    if (id) glUseProgram(id);
}

Result<Shader> Shader::loadFromGLSL(const std::string& vertex, const std::string& fragment) {
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
        return Result<Shader>::fail(std::string(infoLog, length));
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
        return Result<Shader>::fail(std::string(infoLog, length));
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
        return Result<Shader>::fail(std::string(infoLog, length));
    }

    return Shader(program);
}

void Shader::destroy() {
    if (id) glDeleteProgram(id); id = 0;
}