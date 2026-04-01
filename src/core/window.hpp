#ifndef SINGULARITY_WINDOW_HPP
#define SINGULARITY_WINDOW_HPP
#include <string>

class GLFWwindow;

class Window {
public:
    Window(const std::string& title, int width, int height, bool fullscreen);
    ~Window();

    bool init();
    void update();
    static void* getGLProcLoader();
    bool shouldClose();

    int getWidth();
    int getHeight();

private:
    GLFWwindow* window;

    std::string title;
    int width, height;
    bool fullscreen;
};


#endif //SINGULARITY_WINDOW_HPP