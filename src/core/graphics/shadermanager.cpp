#include "shadermanager.hpp"
#include <core/engine.hpp>
#include <util/file.hpp>

namespace singularity {

Shader* ShaderManager::getShader(const std::string& name) {
    if (!Engine::getInstance()) {
        Log::error() << "No engine instance!";
        return nullptr;
    }

    switch (Engine::getInstance()->getRenderer().getType()) {
        case RendererType::OpenGL: {
            std::string vertexPath = "res/shaders/v" + name + ".glsl";
            std::string fragmentPath = "res/shaders/f" + name + ".glsl";

            std::string vertex = readFile(vertexPath);
            if (vertex.length() == 0) {
                Log::error() << "Failed to read vertex shader " << vertexPath << "!";
                return nullptr;
            }

            std::string fragment = readFile(fragmentPath);
            if (fragment.length() == 0) {
                Log::error() << "Failed to read fragment shader " << fragmentPath << "!";
                return nullptr;
            }

            Shader* shader = new Shader(vertex, fragment);
            return shader;
        }

        default:
            return nullptr;
    }
}

}