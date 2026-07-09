#include "windowevent.hpp"

namespace singularity {

WindowEvent::WindowEvent(WindowEventType type) : type(type) {}
WindowEvent::WindowEvent() : type(WindowEventType::Unknown) {}
WindowEvent::~WindowEvent() {}

}