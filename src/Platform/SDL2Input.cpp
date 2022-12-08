//
// SDL2Input.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#include "SDL2Input.h"

namespace Wraith {

    Input::KeyCode Wraith::SDL2Input::TranslateKeyCode(SDL_Keycode sdlKeyCode) {
        switch (sdlKeyCode) {
            case SDLK_UNKNOWN:
                break;
            case SDLK_RETURN:
                return Input::KeyCode::Return;
            case SDLK_ESCAPE:
                break;
            case SDLK_BACKSPACE:
                return Input::KeyCode::Backspace;
            case SDLK_TAB:
                return Input::KeyCode::Tab;
            case SDLK_SPACE:
                return Input::KeyCode::Space;
            case SDLK_EXCLAIM:
                break;
            case SDLK_QUOTEDBL:
                break;
            case SDLK_HASH:
                break;
            case SDLK_PERCENT:
                break;
            case SDLK_DOLLAR:
                break;
            case SDLK_AMPERSAND:
                break;
            case SDLK_QUOTE:
                break;
            case SDLK_LEFTPAREN:
                break;
            case SDLK_RIGHTPAREN:
                break;
            case SDLK_ASTERISK:
                break;
            case SDLK_PLUS:
                break;
            case SDLK_COMMA:
                break;
            case SDLK_MINUS:
                break;
            case SDLK_PERIOD:
                break;
            case SDLK_SLASH:
                break;
            case SDLK_0:
                return Input::KeyCode::Num0;
            case SDLK_1:
                return Input::KeyCode::Num1;
            case SDLK_2:
                return Input::KeyCode::Num2;
            case SDLK_3:
                return Input::KeyCode::Num3;
            case SDLK_4:
                return Input::KeyCode::Num4;
            case SDLK_5:
                return Input::KeyCode::Num5;
            case SDLK_6:
                return Input::KeyCode::Num6;
            case SDLK_7:
                return Input::KeyCode::Num7;
            case SDLK_8:
                return Input::KeyCode::Num8;
            case SDLK_9:
                return Input::KeyCode::Num9;
            case SDLK_COLON:
                break;
            case SDLK_SEMICOLON:
                break;
            case SDLK_LESS:
                break;
            case SDLK_EQUALS:
                break;
            case SDLK_GREATER:
                break;
            case SDLK_QUESTION:
                break;
            case SDLK_AT:
                break;
            case SDLK_LEFTBRACKET:
                break;
            case SDLK_BACKSLASH:
                break;
            case SDLK_RIGHTBRACKET:
                break;
            case SDLK_CARET:
                break;
            case SDLK_UNDERSCORE:
                break;
            case SDLK_BACKQUOTE:
                break;
            case SDLK_a:
                return Input::KeyCode::A;
            case SDLK_b:
                return Input::KeyCode::B;
            case SDLK_c:
                return Input::KeyCode::C;
            case SDLK_d:
                return Input::KeyCode::D;
            case SDLK_e:
                return Input::KeyCode::E;
            case SDLK_f:
                return Input::KeyCode::F;
            case SDLK_g:
                return Input::KeyCode::G;
            case SDLK_h:
                return Input::KeyCode::H;
            case SDLK_i:
                return Input::KeyCode::I;
            case SDLK_j:
                return Input::KeyCode::J;
            case SDLK_k:
                return Input::KeyCode::K;
            case SDLK_l:
                return Input::KeyCode::L;
            case SDLK_m:
                return Input::KeyCode::M;
            case SDLK_n:
                return Input::KeyCode::N;
            case SDLK_o:
                return Input::KeyCode::O;
            case SDLK_p:
                return Input::KeyCode::P;
            case SDLK_q:
                return Input::KeyCode::Q;
            case SDLK_r:
                return Input::KeyCode::R;
            case SDLK_s:
                return Input::KeyCode::S;
            case SDLK_t:
                return Input::KeyCode::T;
            case SDLK_u:
                return Input::KeyCode::U;
            case SDLK_v:
                return Input::KeyCode::V;
            case SDLK_w:
                return Input::KeyCode::W;
            case SDLK_x:
                return Input::KeyCode::X;
            case SDLK_y:
                return Input::KeyCode::Y;
            case SDLK_z:
                return Input::KeyCode::Z;
            case SDLK_CAPSLOCK:
                return Input::KeyCode::CapsLock;
            case SDLK_F1:
                return Input::KeyCode::F1;
            case SDLK_F2:
                return Input::KeyCode::F2;
            case SDLK_F3:
                return Input::KeyCode::F3;
            case SDLK_F4:
                return Input::KeyCode::F4;
            case SDLK_F5:
                return Input::KeyCode::F5;
            case SDLK_F6:
                return Input::KeyCode::F6;
            case SDLK_F7:
                return Input::KeyCode::F7;
            case SDLK_F8:
                return Input::KeyCode::F8;
            case SDLK_F9:
                return Input::KeyCode::F9;
            case SDLK_F10:
                return Input::KeyCode::F10;
            case SDLK_F11:
                return Input::KeyCode::F11;
            case SDLK_F12:
                return Input::KeyCode::F12;
            case SDLK_PRINTSCREEN:
                break;
            case SDLK_SCROLLLOCK:
                break;
            case SDLK_PAUSE:
                break;
            case SDLK_INSERT:
                return Input::KeyCode::Insert;
            case SDLK_HOME:
                return Input::KeyCode::Home;
            case SDLK_PAGEUP:
                break;
            case SDLK_DELETE:
                return Input::KeyCode::Delete;
                break;
            case SDLK_END:
                break;
            case SDLK_PAGEDOWN:
                break;
            case SDLK_RIGHT:
                return Input::KeyCode::ArrowRight;
            case SDLK_LEFT:
                return Input::KeyCode::ArrowLeft;
            case SDLK_DOWN:
                return Input::KeyCode::ArrowDown;
            case SDLK_UP:
                return Input::KeyCode::ArrowUp;
            case SDLK_NUMLOCKCLEAR:
                break;
            case SDLK_KP_DIVIDE:
                break;
            case SDLK_KP_MULTIPLY:
                break;
            case SDLK_KP_MINUS:
                break;
            case SDLK_KP_PLUS:
                break;
            case SDLK_KP_ENTER:
                break;
            case SDLK_KP_1:
                return Input::KeyCode::NumPad1;
            case SDLK_KP_2:
                return Input::KeyCode::NumPad2;
            case SDLK_KP_3:
                return Input::KeyCode::NumPad3;
            case SDLK_KP_4:
                return Input::KeyCode::NumPad4;
            case SDLK_KP_5:
                return Input::KeyCode::NumPad5;
            case SDLK_KP_6:
                return Input::KeyCode::NumPad6;
            case SDLK_KP_7:
                return Input::KeyCode::NumPad7;
            case SDLK_KP_8:
                return Input::KeyCode::NumPad8;
            case SDLK_KP_9:
                return Input::KeyCode::NumPad9;
            case SDLK_KP_0:
                return Input::KeyCode::NumPad0;
            case SDLK_KP_PERIOD:
                break;
            case SDLK_APPLICATION:
                break;
            case SDLK_POWER:
                break;
            case SDLK_KP_EQUALS:
                break;
            case SDLK_F13:
                return Input::KeyCode::F13;
            case SDLK_F14:
                return Input::KeyCode::F14;
            case SDLK_F15:
                return Input::KeyCode::F15;
            case SDLK_F16:
                return Input::KeyCode::F16;
            case SDLK_F17:
                return Input::KeyCode::F17;
            case SDLK_F18:
                return Input::KeyCode::F18;
            case SDLK_F19:
                return Input::KeyCode::F19;
            case SDLK_F20:
                return Input::KeyCode::F20;
            case SDLK_F21:
                return Input::KeyCode::F21;
            case SDLK_F22:
                return Input::KeyCode::F22;
            case SDLK_F23:
                return Input::KeyCode::F23;
            case SDLK_F24:
                return Input::KeyCode::F24;
            case SDLK_EXECUTE:
                break;
            case SDLK_HELP:
                break;
            case SDLK_MENU:
                break;
            case SDLK_SELECT:
                break;
            case SDLK_STOP:
                break;
            case SDLK_AGAIN:
                break;
            case SDLK_UNDO:
                break;
            case SDLK_CUT:
                break;
            case SDLK_COPY:
                break;
            case SDLK_PASTE:
                break;
            case SDLK_FIND:
                break;
            case SDLK_MUTE:
                break;
            case SDLK_VOLUMEUP:
                break;
            case SDLK_VOLUMEDOWN:
                break;
            case SDLK_KP_COMMA:
                break;
            case SDLK_KP_EQUALSAS400:
                break;
            case SDLK_ALTERASE:
                break;
            case SDLK_SYSREQ:
                break;
            case SDLK_CANCEL:
                break;
            case SDLK_CLEAR:
                break;
            case SDLK_PRIOR:
                break;
            case SDLK_RETURN2:
                break;
            case SDLK_SEPARATOR:
                break;
            case SDLK_OUT:
                break;
            case SDLK_OPER:
                break;
            case SDLK_CLEARAGAIN:
                break;
            case SDLK_CRSEL:
                break;
            case SDLK_EXSEL:
                break;
            case SDLK_KP_00:
                break;
            case SDLK_KP_000:
                break;
            case SDLK_THOUSANDSSEPARATOR:
                break;
            case SDLK_DECIMALSEPARATOR:
                break;
            case SDLK_CURRENCYUNIT:
                break;
            case SDLK_CURRENCYSUBUNIT:
                break;
            case SDLK_KP_LEFTPAREN:
                break;
            case SDLK_KP_RIGHTPAREN:
                break;
            case SDLK_KP_LEFTBRACE:
                break;
            case SDLK_KP_RIGHTBRACE:
                break;
            case SDLK_KP_TAB:
                break;
            case SDLK_KP_BACKSPACE:
                break;
            case SDLK_KP_A:
                break;
            case SDLK_KP_B:
                break;
            case SDLK_KP_C:
                break;
            case SDLK_KP_D:
                break;
            case SDLK_KP_E:
                break;
            case SDLK_KP_F:
                break;
            case SDLK_KP_XOR:
                break;
            case SDLK_KP_POWER:
                break;
            case SDLK_KP_PERCENT:
                break;
            case SDLK_KP_LESS:
                break;
            case SDLK_KP_GREATER:
                break;
            case SDLK_KP_AMPERSAND:
                break;
            case SDLK_KP_DBLAMPERSAND:
                break;
            case SDLK_KP_VERTICALBAR:
                break;
            case SDLK_KP_DBLVERTICALBAR:
                break;
            case SDLK_KP_COLON:
                break;
            case SDLK_KP_HASH:
                break;
            case SDLK_KP_SPACE:
                break;
            case SDLK_KP_AT:
                break;
            case SDLK_KP_EXCLAM:
                break;
            case SDLK_KP_MEMSTORE:
                break;
            case SDLK_KP_MEMRECALL:
                break;
            case SDLK_KP_MEMCLEAR:
                break;
            case SDLK_KP_MEMADD:
                break;
            case SDLK_KP_MEMSUBTRACT:
                break;
            case SDLK_KP_MEMMULTIPLY:
                break;
            case SDLK_KP_MEMDIVIDE:
                break;
            case SDLK_KP_PLUSMINUS:
                break;
            case SDLK_KP_CLEAR:
                break;
            case SDLK_KP_CLEARENTRY:
                break;
            case SDLK_KP_BINARY:
                break;
            case SDLK_KP_OCTAL:
                break;
            case SDLK_KP_DECIMAL:
                break;
            case SDLK_KP_HEXADECIMAL:
                break;
            case SDLK_LCTRL:
                return Input::KeyCode::LCtrl;
            case SDLK_LSHIFT:
                return Input::KeyCode::LShift;
            case SDLK_LALT:
                return Input::KeyCode::LAlt;
            case SDLK_LGUI:
                break;
            case SDLK_RCTRL:
                return Input::KeyCode::RCtrl;
            case SDLK_RSHIFT:
                return Input::KeyCode::RShift;
            case SDLK_RALT:
                return Input::KeyCode::RAlt;
            case SDLK_RGUI:
                break;
            case SDLK_MODE:
                break;
            case SDLK_AUDIONEXT:
                break;
            case SDLK_AUDIOPREV:
                break;
            case SDLK_AUDIOSTOP:
                break;
            case SDLK_AUDIOPLAY:
                break;
            case SDLK_AUDIOMUTE:
                break;
            case SDLK_MEDIASELECT:
                break;
            case SDLK_WWW:
                break;
            case SDLK_MAIL:
                break;
            case SDLK_CALCULATOR:
                break;
            case SDLK_COMPUTER:
                break;
            case SDLK_AC_SEARCH:
                break;
            case SDLK_AC_HOME:
                break;
            case SDLK_AC_BACK:
                break;
            case SDLK_AC_FORWARD:
                break;
            case SDLK_AC_STOP:
                break;
            case SDLK_AC_REFRESH:
                break;
            case SDLK_AC_BOOKMARKS:
                break;
            case SDLK_BRIGHTNESSDOWN:
                break;
            case SDLK_BRIGHTNESSUP:
                break;
            case SDLK_DISPLAYSWITCH:
                break;
            case SDLK_KBDILLUMTOGGLE:
                break;
            case SDLK_KBDILLUMDOWN:
                break;
            case SDLK_KBDILLUMUP:
                break;
            case SDLK_EJECT:
                break;
            case SDLK_SLEEP:
                break;
            case SDLK_APP1:
                break;
            case SDLK_APP2:
                break;
            case SDLK_AUDIOREWIND:
                break;
            case SDLK_AUDIOFASTFORWARD:
                break;
            default:
                return Input::KeyCode::Unknown;
        }
        return Input::KeyCode::Unknown;
    }

    Input::MouseButton Wraith::SDL2Input::TranslateMouseButton(Uint8 sdlMouseButton) {
        switch(sdlMouseButton) {
            case SDL_BUTTON_LEFT:
                return Input::MouseButton::Left;
            case SDL_BUTTON_RIGHT:
                return Input::MouseButton::Right;
            case SDL_BUTTON_MIDDLE:
                return Input::MouseButton::Middle;
            default:
                return Input::MouseButton::Unknown;
        }
    }

}