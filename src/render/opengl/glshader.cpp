#include "glshader.hpp"
#include <glad/glad.h>
#include <logger/logger.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace singularity {

GLShader::GLShader() : id(0) {}
GLShader::~GLShader() {}

bool GLShader::compileGLSL(const std::string& vertex, const std::string& fragment) {
    const char* cVert = vertex.c_str();
    const char* cFrag = fragment.c_str();

    char log[1024];
    int success;

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &cVert, nullptr);
    glCompileShader(vShader);
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShader, 1024, nullptr, log);
        Log::error() << "Failed to compile vertex shader:\n" << log;
        glDeleteShader(vShader);
        return false;
    }

    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &cFrag, nullptr);
    glCompileShader(fShader);
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fShader, 1024, nullptr, log);
        Log::error() << "Failed to compile fragment shader:\n" << log;
        glDeleteShader(vShader);
        glDeleteShader(fShader);
        return false;
    }

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vShader);
    glAttachShader(prog, fShader);
    glLinkProgram(prog);
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(prog, 1024, nullptr, log);
        Log::error() << "Failed to link shader program:\n" << log;
        glDeleteShader(vShader);
        glDeleteShader(fShader);
        glDeleteProgram(prog);
        return false;
    }

    // delete unused shaders
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    id = prog;

    return true;
}

void GLShader::use() {
    if (id) glUseProgram(id);
}

void GLShader::destroy() {
    if (id) glDeleteProgram(id);
}

void GLShader::setMat4(const std::string& name, const glm::mat4& matrix) {
    if (!id) return;
    
    GLint loc = glGetUniformLocation(id, name.c_str());
    if (loc < 0) {
        Log::error() << "Uniform " << name << " is not found!";
        return;
    }

    glUniformMatrix4fv(loc, 1, false, glm::value_ptr(matrix));
}

}