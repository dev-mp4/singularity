#ifndef SINGULARITY_WINDOW_HPP
#define SINGULARITY_WINDOW_HPP
#include <string>

class GLFWwindow;

namespace singularity {

typedef void (*KeyCallbackFn)(GLFWwindow*, int, int, int, int);
typedef void (*MouseCallbackFn)(GLFWwindow*, int, int, int);
typedef void (*CursorPosCallbackFn)(GLFWwindow*, double, double);

class Window {
public:
    Window();
    ~Window();

    bool init(const std::string& title, int width, int height, bool fullscreen);
    void update();
    static void* getGLProcLoader();
    bool shouldClose();

    int getWidth();
    int getHeight();

    static double getTime();

    void destroy();

    void setKeyCallback(KeyCallbackFn callback);
    void setMouseCallback(MouseCallbackFn callback);
    void setMousePosCallback(CursorPosCallbackFn callback);

    void setCursorState(bool state);

private:
    GLFWwindow* window;

    std::string title;
    int width, height;
    bool fullscreen;
};

}

#endif //SINGULARITY_WINDOW_HPP