#ifndef SINGULARITY_ISHADER_HPP
#define SINGULARITY_ISHADER_HPP

class IShader {
public:
    virtual ~IShader() = default;

    virtual void use() = 0;
    virtual void destroy() = 0;
};

#endif // SINGULARITY_ISHADER_HPP