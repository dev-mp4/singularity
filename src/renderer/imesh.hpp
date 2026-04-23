#ifndef SINGULARITY_IMESH_HPP
#define SINGULARITY_IMESH_HPP

class IMesh {
public:
    virtual ~IMesh() = default;

    virtual void draw() = 0;
    virtual void destroy() = 0;  
};

#endif // SINGULARITY_IMESH_HPP