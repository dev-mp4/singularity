#include "input.hpp"
#include <GLFW/glfw3.h>

namespace singularity {

Input::Input() {}
Input::~Input() {}

static Input* self = nullptr;

void keyCallback(GLFWwindow* w, int key, int scancode, int action, int mods) {
    if (self == nullptr) return;
    
    if (action == GLFW_PRESS) self->setKeyState(key, true);
    else if (action == GLFW_RELEASE) self->setKeyState(key, false);
}

void mouseCallback(GLFWwindow* w, int button, int action, int mods) {
    if (self == nullptr) return;

    if (action == GLFW_PRESS) self->setKeyState(1024 + button, true);
    else if (action == GLFW_RELEASE) self->setKeyState(1024 + button, false);
}

void mousePosCallback(GLFWwindow* w, double x, double y) {
    if (self == nullptr) return;

    self->setMousePos(glm::vec2(x, y));
}

void Input::init(Window& window) {
    currentFrame.reset();
    previvousFrame.reset();
    mouseCurrentFrame.reset();
    mousePrevivousFrame.reset();

    self = this;

    window.setKeyCallback(keyCallback);
    window.setMouseCallback(mouseCallback);
    window.setMousePosCallback(mousePosCallback);
}

void Input::destroy() {
    self = nullptr;
}

void Input::poll() {
    previvousFrame = currentFrame;
    mousePrevivousFrame = mouseCurrentFrame;

    mouseDelta = glm::vec2(0, 0);

    glfwPollEvents();
}

bool Input::getKey(int key) {
    if (key > 1024 || key < 0) return false;
    return currentFrame.test(key);
}

bool Input::getKeyDown(int key) {
    if (key > 1024 || key < 0) return false;
    return currentFrame.test(key) && !previvousFrame.test(key);
}

bool Input::getKeyUp(int key) {
    if (key > 1024 || key < 0) return false;
    return !currentFrame.test(key) && previvousFrame.test(key);
}


bool Input::getMouseButton(int button) {
    if (button > 8 || button < 0) return false;
    return mouseCurrentFrame.test(button);
}

bool Input::getMouseButtonDown(int button) {
    if (button > 8 || button < 0) return false;
    return mouseCurrentFrame.test(button) && !mousePrevivousFrame.test(button);
}

bool Input::getMouseButtonUp(int button) {
    if (button > 8 || button < 0) return false;
    return !mouseCurrentFrame.test(button) && mousePrevivousFrame.test(button);
}


glm::vec2 Input::getMousePos() {
    return mousePos;
}

glm::vec2 Input::getMouseDelta() {
    return mouseDelta;
}


void Input::setKeyState(int key, bool state) {
    if (key <= 1024) currentFrame.set(key, state);
    else if (key > 1024) mouseCurrentFrame.set(key - 1024, state);
}

void Input::setMousePos(glm::vec2 pos) {
    mouseDelta += pos - mousePos;
    mousePos = pos;
}

}