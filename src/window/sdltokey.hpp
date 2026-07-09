#ifndef SINGULARITY_SDLTOKEY_HPP
#define SINGULARITY_SDLTOKEY_HPP

#include "SDL3/SDL_scancode.h"
#include <core/keycode.hpp>
#include <SDL3/SDL.h>

namespace singularity {

inline KeyCode SDLtoKey(SDL_Scancode key) {
    switch (key) {
        case SDL_SCANCODE_UNKNOWN: return KeyCode::Unknown;

        case SDL_SCANCODE_A: return KeyCode::A;
        case SDL_SCANCODE_B: return KeyCode::B;
        case SDL_SCANCODE_C: return KeyCode::C;
        case SDL_SCANCODE_D: return KeyCode::D;
        case SDL_SCANCODE_E: return KeyCode::E;
        case SDL_SCANCODE_F: return KeyCode::F;
        case SDL_SCANCODE_G: return KeyCode::G;
        case SDL_SCANCODE_H: return KeyCode::H;
        case SDL_SCANCODE_I: return KeyCode::I;
        case SDL_SCANCODE_J: return KeyCode::J;
        case SDL_SCANCODE_K: return KeyCode::K;
        case SDL_SCANCODE_L: return KeyCode::L;
        case SDL_SCANCODE_M: return KeyCode::M;
        case SDL_SCANCODE_N: return KeyCode::N;
        case SDL_SCANCODE_O: return KeyCode::O;
        case SDL_SCANCODE_P: return KeyCode::P;
        case SDL_SCANCODE_Q: return KeyCode::Q;
        case SDL_SCANCODE_R: return KeyCode::R;
        case SDL_SCANCODE_S: return KeyCode::S;
        case SDL_SCANCODE_T: return KeyCode::T;
        case SDL_SCANCODE_U: return KeyCode::U;
        case SDL_SCANCODE_V: return KeyCode::V;
        case SDL_SCANCODE_W: return KeyCode::W;
        case SDL_SCANCODE_X: return KeyCode::X;
        case SDL_SCANCODE_Y: return KeyCode::Y;
        case SDL_SCANCODE_Z: return KeyCode::Z;

        case SDL_SCANCODE_1: return KeyCode::Num1;
        case SDL_SCANCODE_2: return KeyCode::Num2;
        case SDL_SCANCODE_3: return KeyCode::Num3;
        case SDL_SCANCODE_4: return KeyCode::Num4;
        case SDL_SCANCODE_5: return KeyCode::Num5;
        case SDL_SCANCODE_6: return KeyCode::Num6;
        case SDL_SCANCODE_7: return KeyCode::Num7;
        case SDL_SCANCODE_8: return KeyCode::Num8;
        case SDL_SCANCODE_9: return KeyCode::Num9;
        case SDL_SCANCODE_0: return KeyCode::Num0;

        case SDL_SCANCODE_RETURN: return KeyCode::Enter;
        case SDL_SCANCODE_ESCAPE: return KeyCode::Escape;
        case SDL_SCANCODE_BACKSPACE: return KeyCode::Backspace;
        case SDL_SCANCODE_TAB: return KeyCode::Tab;
        case SDL_SCANCODE_SPACE: return KeyCode::Space;
        case SDL_SCANCODE_MINUS: return KeyCode::Minus;
        case SDL_SCANCODE_EQUALS: return KeyCode::Equals;
        case SDL_SCANCODE_LEFTBRACKET: return KeyCode::LeftBracket;
        case SDL_SCANCODE_RIGHTBRACKET: return KeyCode::RightBracket;
        case SDL_SCANCODE_BACKSLASH: return KeyCode::Backslash;
        case SDL_SCANCODE_SEMICOLON: return KeyCode::Semicolon;
        case SDL_SCANCODE_APOSTROPHE: return KeyCode::Apostrophe;
        case SDL_SCANCODE_COMMA: return KeyCode::Comma;
        case SDL_SCANCODE_PERIOD: return KeyCode::Period;
        case SDL_SCANCODE_SLASH: return KeyCode::Slash;
        case SDL_SCANCODE_CAPSLOCK: return KeyCode::CapsLock;

        case SDL_SCANCODE_F1: return KeyCode::F1;
        case SDL_SCANCODE_F2: return KeyCode::F2;
        case SDL_SCANCODE_F3: return KeyCode::F3;
        case SDL_SCANCODE_F4: return KeyCode::F4;
        case SDL_SCANCODE_F5: return KeyCode::F5;
        case SDL_SCANCODE_F6: return KeyCode::F6;
        case SDL_SCANCODE_F7: return KeyCode::F7;
        case SDL_SCANCODE_F8: return KeyCode::F8;
        case SDL_SCANCODE_F9: return KeyCode::F9;
        case SDL_SCANCODE_F10: return KeyCode::F10;
        case SDL_SCANCODE_F11: return KeyCode::F11;
        case SDL_SCANCODE_F12: return KeyCode::F12;
        case SDL_SCANCODE_F13: return KeyCode::F13;
        case SDL_SCANCODE_F14: return KeyCode::F14;
        case SDL_SCANCODE_F15: return KeyCode::F15;
        case SDL_SCANCODE_F16: return KeyCode::F16;
        case SDL_SCANCODE_F17: return KeyCode::F17;
        case SDL_SCANCODE_F18: return KeyCode::F18;
        case SDL_SCANCODE_F19: return KeyCode::F19;
        case SDL_SCANCODE_F20: return KeyCode::F20;
        case SDL_SCANCODE_F21: return KeyCode::F21;
        case SDL_SCANCODE_F22: return KeyCode::F22;
        case SDL_SCANCODE_F23: return KeyCode::F23;
        case SDL_SCANCODE_F24: return KeyCode::F24;

        case SDL_SCANCODE_PRINTSCREEN: return KeyCode::PrintScreen;
        case SDL_SCANCODE_SCROLLLOCK: return KeyCode::ScrollLock;
        case SDL_SCANCODE_PAUSE: return KeyCode::Pause;
        case SDL_SCANCODE_INSERT: return KeyCode::Insert;
        case SDL_SCANCODE_HOME: return KeyCode::Home;
        case SDL_SCANCODE_PAGEUP: return KeyCode::PageUp;
        case SDL_SCANCODE_DELETE: return KeyCode::Delete;
        case SDL_SCANCODE_END: return KeyCode::End;
        case SDL_SCANCODE_PAGEDOWN: return KeyCode::PageDown;

        case SDL_SCANCODE_RIGHT: return KeyCode::Right;
        case SDL_SCANCODE_LEFT: return KeyCode::Left;
        case SDL_SCANCODE_DOWN: return KeyCode::Down;
        case SDL_SCANCODE_UP: return KeyCode::Up;

        case SDL_SCANCODE_NUMLOCKCLEAR: return KeyCode::NumLock;
        case SDL_SCANCODE_KP_DIVIDE: return KeyCode::KPDivide;
        case SDL_SCANCODE_KP_MULTIPLY: return KeyCode::KPMultiply;
        case SDL_SCANCODE_KP_MINUS: return KeyCode::KPSubtract;
        case SDL_SCANCODE_KP_PLUS: return KeyCode::KPAdd;
        case SDL_SCANCODE_KP_ENTER: return KeyCode::KPEnter;
        case SDL_SCANCODE_KP_1: return KeyCode::KP1;
        case SDL_SCANCODE_KP_2: return KeyCode::KP2;
        case SDL_SCANCODE_KP_3: return KeyCode::KP3;
        case SDL_SCANCODE_KP_4: return KeyCode::KP4;
        case SDL_SCANCODE_KP_5: return KeyCode::KP5;
        case SDL_SCANCODE_KP_6: return KeyCode::KP6;
        case SDL_SCANCODE_KP_7: return KeyCode::KP7;
        case SDL_SCANCODE_KP_8: return KeyCode::KP8;
        case SDL_SCANCODE_KP_9: return KeyCode::KP9;
        case SDL_SCANCODE_KP_0: return KeyCode::KP0;
        case SDL_SCANCODE_KP_PERIOD: return KeyCode::KPPeriod;
        case SDL_SCANCODE_KP_EQUALS: return KeyCode::KPEquals;

        case SDL_SCANCODE_MENU: return KeyCode::Menu;
        case SDL_SCANCODE_GRAVE: return KeyCode::Grave;

        case SDL_SCANCODE_LSHIFT: return KeyCode::LeftShift;
        case SDL_SCANCODE_RSHIFT: return KeyCode::RightShift;
        case SDL_SCANCODE_LCTRL: return KeyCode::LeftControl;
        case SDL_SCANCODE_RCTRL: return KeyCode::RightControl;
        case SDL_SCANCODE_LALT: return KeyCode::LeftAlt;
        case SDL_SCANCODE_RALT: return KeyCode::RightAlt;
        case SDL_SCANCODE_LGUI: return KeyCode::LeftSuper;
        case SDL_SCANCODE_RGUI: return KeyCode::RightSuper;

        case SDL_SCANCODE_KP_DECIMAL: return KeyCode::KPDecimal;
        
        case SDL_SCANCODE_MEDIA_NEXT_TRACK: return KeyCode::MediaNextTrack;
        case SDL_SCANCODE_MEDIA_PREVIOUS_TRACK: return KeyCode::MediaPreviousTrack;
        case SDL_SCANCODE_MEDIA_STOP: return KeyCode::MediaStop;
        case SDL_SCANCODE_MEDIA_PLAY_PAUSE: return KeyCode::MediaPlayPause;
        case SDL_SCANCODE_MUTE: return KeyCode::Mute;
        case SDL_SCANCODE_VOLUMEUP: return KeyCode::VolumeUp;
        case SDL_SCANCODE_VOLUMEDOWN: return KeyCode::VolumeDown;
        default: return KeyCode::Unknown;
    }
}

}

#endif