#ifndef SINGULARITY_WINDOWEVENT_HPP
#define SINGULARITY_WINDOWEVENT_HPP

#include <core/keycode.hpp>

namespace singularity {

enum class WindowEventType {
    Unknown,
    Quit,
    KeyPress,
    MouseClick,
    MouseMotion,
    MouseWheel
};

struct KeyEvent {
    KeyCode key = KeyCode::Unknown;
    bool down = false;
};

struct MouseClickEvent {
    int button = -1;
    bool down = false;
};

struct MouseMotionEvent {
    double x = 0;
    double y = 0;
};

struct MouseWheelEvent {
    float scroll = 0;
};

class WindowEvent {
public:
    WindowEvent(WindowEventType type);
    WindowEvent();
    ~WindowEvent();

    WindowEventType type;
    KeyEvent key;
    MouseClickEvent mouseclick;
    MouseMotionEvent mousemotion;
    MouseWheelEvent mousewheel;
};

}

#endif