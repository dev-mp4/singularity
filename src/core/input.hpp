#ifndef SINGULARITY_INPUT_HPP
#define SINGULARITY_INPUT_HPP

#include <bitset>
#include <window/window.hpp>

namespace singularity {

struct KeyEvent {
    KeyCode key;
    bool isPressed;
};

struct MouseClickEvent {
    int button;
    bool isPressed;
};

struct QuitEvent {};

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
};

}

#endif