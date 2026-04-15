#ifndef SINGULARITY_WINDOW_HPP
#define SINGULARITY_WINDOW_HPP
#include <string>

class GLFWwindow;

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

private:
    GLFWwindow* window;

    std::string title;
    int width, height;
    bool fullscreen;
};


#endif //SINGULARITY_WINDOW_HPP