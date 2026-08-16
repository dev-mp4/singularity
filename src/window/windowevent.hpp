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

struct WindowKeyEvent {
    KeyCode key = KeyCode::Unknown;
    bool down = false;
};

struct WindowMouseClickEvent {
    int button = -1;
    bool down = false;
};

struct WindowMouseMotionEvent {
    double x = 0;
    double y = 0;
};

struct WindowMouseWheelEvent {
    float scroll = 0;
};

class WindowEvent {
public:
    WindowEvent(WindowEventType type);
    WindowEvent();
    ~WindowEvent();

    WindowEventType type;
    WindowKeyEvent key;
    WindowMouseClickEvent mouseclick;
    WindowMouseMotionEvent mousemotion;
    WindowMouseWheelEvent mousewheel;
};

}

#endif