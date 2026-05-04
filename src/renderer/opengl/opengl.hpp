#ifndef SINGULARITY_OPENGL_HPP
#define SINGULARITY_OPENGL_HPP

namespace singularity {

class OpenGL {
public:
    static bool init(int width, int height);
    static void clear(float r, float g, float b);
};

}

#endif //SINGULARITY_OPENGL_HPP