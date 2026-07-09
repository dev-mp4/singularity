#ifndef SINGULARITY_INPUT_HPP
#define SINGULARITY_INPUT_HPP

#include <bitset>
#include <window/window.hpp>

namespace singularity {

class Input {
public:
    Input(Window& window);
    ~Input();

    bool init();
    void destroy();

    void update();

    bool getKeyDown(KeyCode key);
    bool getKeyUp(KeyCode key);
    bool getKey(KeyCode key);

    bool getMouseButtonDown(int button);
    bool getMouseButtonUp(int button);
    bool getMouseButton(int button);

    float getMouseDeltaX();
    float getMouseDeltaY();
    float getMouseX();
    float getMouseY();

    float getScrollValue();

    bool isShouldClose();

private:
    Window& window;

    std::bitset<126> keys;
    std::bitset<126> prevKeys;
    std::bitset<32> mouseButtons;
    std::bitset<32> prevMouseButtons;

    float mouseX;
    float mouseY;
    float mouseDeltaX;
    float mouseDeltaY;
    float scroll;

    bool shouldClose;
};

}

#endif