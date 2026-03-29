#ifndef SINGULARITY_WINDOW_HPP
#define SINGULARITY_WINDOW_HPP
#include <string>

class GLFWwindow;

class Window {
public:
    Window(const std::string& title, int width, int height, bool fullscreen);
    ~Window();

    bool init();
    void update() const;
    static void* getGLProcLoader();
    bool shouldClose() const;

    int getWidth() const;
    int getHeight() const;

private:
    GLFWwindow* window;

    std::string title;
    int width, height;
    bool fullscreen;
};


#endif //SINGULARITY_WINDOW_HPP