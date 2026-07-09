#ifndef SINGULARITY_ISHADER_HPP
#define SINGULARITY_ISHADER_HPP

#include <string>

namespace singularity {

class IShader {
public:
    virtual ~IShader() = default;

    virtual bool compileGLSL(const std::string& vertex, const std::string& fragment) = 0;

    virtual void use() = 0;
    virtual void destroy() = 0;
};

}

#endif