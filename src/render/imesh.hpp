#ifndef SINGULARITY_IMESH_HPP
#define SINGULARITY_IMESH_HPP

#include <vector>

namespace singularity {

class IMesh {
public:
    virtual ~IMesh() = default;

    virtual bool create(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned short>& attributes) = 0;

    virtual void draw() = 0;
    virtual void destroy() = 0;
};

}

#endif