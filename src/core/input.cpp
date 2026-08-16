#include "input.hpp"
#include <window/windowevent.hpp>
#include <window/window.hpp>
#include <core/engine.hpp>

namespace singularity {

Input::Input(Window& window) : window(window) {}
Input::~Input() {}

bool Input::init() {
    keys.reset();
    prevKeys.reset();
    mouseButtons.reset();
    prevMouseButtons.reset();

    mouseX = 0.0f;
    mouseY = 0.0f;
    mouseDeltaX = 0.0f;
    mouseDeltaY = 0.0f;
    scroll = 0.0f;

    return true;
}

void Input::destroy() {
    // ...
}

void Input::update() {
    Engine* engine = Engine::getInstance();
    if (!engine) return;

    mouseDeltaX = 0.0f;
    mouseDeltaY = 0.0f;
    scroll = 0.0f;

    prevKeys = keys;
    prevMouseButtons = mouseButtons;

    WindowEvent event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case WindowEventType::KeyPress:
                keys.set((int) event.key.key, event.key.down);
                engine->getEventBus().post<KeyEvent>({event.key.key, event.key.down});
                break;
            case WindowEventType::MouseClick:
                if (event.mouseclick.button < 32) {
                    mouseButtons.set(event.mouseclick.button, event.mouseclick.down);
                    engine->getEventBus().post<MouseClickEvent>({event.mouseclick.button, event.mouseclick.down});
                }
                break;
            case WindowEventType::MouseMotion:
                mouseDeltaX += event.mousemotion.x - mouseX;
                mouseDeltaY += event.mousemotion.y - mouseY;
                mouseX = event.mousemotion.x;
                mouseY = event.mousemotion.y;
                break;
            case WindowEventType::MouseWheel:
                scroll += event.mousewheel.scroll;
                break;
            case WindowEventType::Quit:
                engine->getEventBus().post<QuitEvent>({});
            default:
                break;
        }
    }
}

bool Input::getKeyDown(KeyCode key) {
    return keys.test((int) key) && !prevKeys.test((int) key);
}

bool Input::getKeyUp(KeyCode key) {
    return !keys.test((int) key) && prevKeys.test((int) key);
}

bool Input::getKey(KeyCode key) {
    return keys.test((int) key);
}

bool Input::getMouseButtonDown(int button) {
    return mouseButtons.test(button) && !prevMouseButtons.test(button);
}

bool Input::getMouseButtonUp(int button) {
    return !mouseButtons.test(button) && prevMouseButtons.test(button);
}

bool Input::getMouseButton(int button) {
    return mouseButtons.test(button);
}

float Input::getMouseDeltaX() {
    return mouseDeltaX;
}

float Input::getMouseDeltaY() {
    return mouseDeltaY;
}

float Input::getMouseX() {
    return mouseX;
}

float Input::getMouseY() {
    return mouseY;
}

float Input::getScrollValue() {
    return scroll;
}


}