//
// SDL2Input.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#include "SDL2Input.h"

namespace Wraith {

    Input::EKeyCode Wraith::SDL2Input::TranslateKeyCode(SDL_Keycode sdlKeyCode) {
        switch (sdlKeyCode) {
            case SDLK_UNKNOWN:
                break;
            case SDLK_RETURN:
                return Input::EKeyCode::Return;
            case SDLK_ESCAPE:
                break;
            case SDLK_BACKSPACE:
                return Input::EKeyCode::Backspace;
            case SDLK_TAB:
                return Input::EKeyCode::Tab;
            case SDLK_SPACE:
                return Input::EKeyCode::Space;
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
                return Input::EKeyCode::Num0;
            case SDLK_1:
                return Input::EKeyCode::Num1;
            case SDLK_2:
                return Input::EKeyCode::Num2;
            case SDLK_3:
                return Input::EKeyCode::Num3;
            case SDLK_4:
                return Input::EKeyCode::Num4;
            case SDLK_5:
                return Input::EKeyCode::Num5;
            case SDLK_6:
                return Input::EKeyCode::Num6;
            case SDLK_7:
                return Input::EKeyCode::Num7;
            case SDLK_8:
                return Input::EKeyCode::Num8;
            case SDLK_9:
                return Input::EKeyCode::Num9;
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
                return Input::EKeyCode::A;
            case SDLK_b:
                return Input::EKeyCode::B;
            case SDLK_c:
                return Input::EKeyCode::C;
            case SDLK_d:
                return Input::EKeyCode::D;
            case SDLK_e:
                return Input::EKeyCode::E;
            case SDLK_f:
                return Input::EKeyCode::F;
            case SDLK_g:
                return Input::EKeyCode::G;
            case SDLK_h:
                return Input::EKeyCode::H;
            case SDLK_i:
                return Input::EKeyCode::I;
            case SDLK_j:
                return Input::EKeyCode::J;
            case SDLK_k:
                return Input::EKeyCode::K;
            case SDLK_l:
                return Input::EKeyCode::L;
            case SDLK_m:
                return Input::EKeyCode::M;
            case SDLK_n:
                return Input::EKeyCode::N;
            case SDLK_o:
                return Input::EKeyCode::O;
            case SDLK_p:
                return Input::EKeyCode::P;
            case SDLK_q:
                return Input::EKeyCode::Q;
            case SDLK_r:
                return Input::EKeyCode::R;
            case SDLK_s:
                return Input::EKeyCode::S;
            case SDLK_t:
                return Input::EKeyCode::T;
            case SDLK_u:
                return Input::EKeyCode::U;
            case SDLK_v:
                return Input::EKeyCode::V;
            case SDLK_w:
                return Input::EKeyCode::W;
            case SDLK_x:
                return Input::EKeyCode::X;
            case SDLK_y:
                return Input::EKeyCode::Y;
            case SDLK_z:
                return Input::EKeyCode::Z;
            case SDLK_CAPSLOCK:
                return Input::EKeyCode::CapsLock;
            case SDLK_F1:
                return Input::EKeyCode::F1;
            case SDLK_F2:
                return Input::EKeyCode::F2;
            case SDLK_F3:
                return Input::EKeyCode::F3;
            case SDLK_F4:
                return Input::EKeyCode::F4;
            case SDLK_F5:
                return Input::EKeyCode::F5;
            case SDLK_F6:
                return Input::EKeyCode::F6;
            case SDLK_F7:
                return Input::EKeyCode::F7;
            case SDLK_F8:
                return Input::EKeyCode::F8;
            case SDLK_F9:
                return Input::EKeyCode::F9;
            case SDLK_F10:
                return Input::EKeyCode::F10;
            case SDLK_F11:
                return Input::EKeyCode::F11;
            case SDLK_F12:
                return Input::EKeyCode::F12;
            case SDLK_PRINTSCREEN:
                break;
            case SDLK_SCROLLLOCK:
                break;
            case SDLK_PAUSE:
                break;
            case SDLK_INSERT:
                return Input::EKeyCode::Insert;
            case SDLK_HOME:
                return Input::EKeyCode::Home;
            case SDLK_PAGEUP:
                break;
            case SDLK_DELETE:
                return Input::EKeyCode::Delete;
                break;
            case SDLK_END:
                break;
            case SDLK_PAGEDOWN:
                break;
            case SDLK_RIGHT:
                return Input::EKeyCode::ArrowRight;
            case SDLK_LEFT:
                return Input::EKeyCode::ArrowLeft;
            case SDLK_DOWN:
                return Input::EKeyCode::ArrowDown;
            case SDLK_UP:
                return Input::EKeyCode::ArrowUp;
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
                return Input::EKeyCode::NumPad1;
            case SDLK_KP_2:
                return Input::EKeyCode::NumPad2;
            case SDLK_KP_3:
                return Input::EKeyCode::NumPad3;
            case SDLK_KP_4:
                return Input::EKeyCode::NumPad4;
            case SDLK_KP_5:
                return Input::EKeyCode::NumPad5;
            case SDLK_KP_6:
                return Input::EKeyCode::NumPad6;
            case SDLK_KP_7:
                return Input::EKeyCode::NumPad7;
            case SDLK_KP_8:
                return Input::EKeyCode::NumPad8;
            case SDLK_KP_9:
                return Input::EKeyCode::NumPad9;
            case SDLK_KP_0:
                return Input::EKeyCode::NumPad0;
            case SDLK_KP_PERIOD:
                break;
            case SDLK_APPLICATION:
                break;
            case SDLK_POWER:
                break;
            case SDLK_KP_EQUALS:
                break;
            case SDLK_F13:
                return Input::EKeyCode::F13;
            case SDLK_F14:
                return Input::EKeyCode::F14;
            case SDLK_F15:
                return Input::EKeyCode::F15;
            case SDLK_F16:
                return Input::EKeyCode::F16;
            case SDLK_F17:
                return Input::EKeyCode::F17;
            case SDLK_F18:
                return Input::EKeyCode::F18;
            case SDLK_F19:
                return Input::EKeyCode::F19;
            case SDLK_F20:
                return Input::EKeyCode::F20;
            case SDLK_F21:
                return Input::EKeyCode::F21;
            case SDLK_F22:
                return Input::EKeyCode::F22;
            case SDLK_F23:
                return Input::EKeyCode::F23;
            case SDLK_F24:
                return Input::EKeyCode::F24;
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
                return Input::EKeyCode::LCtrl;
            case SDLK_LSHIFT:
                return Input::EKeyCode::LShift;
            case SDLK_LALT:
                return Input::EKeyCode::LAlt;
            case SDLK_LGUI:
                break;
            case SDLK_RCTRL:
                return Input::EKeyCode::RCtrl;
            case SDLK_RSHIFT:
                return Input::EKeyCode::RShift;
            case SDLK_RALT:
                return Input::EKeyCode::RAlt;
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
                return Input::EKeyCode::Unknown;
        }
        return Input::EKeyCode::Unknown;
    }

    Input::EMouseButton Wraith::SDL2Input::TranslateMouseButton(Uint8 sdlMouseButton) {
        switch(sdlMouseButton) {
            case SDL_BUTTON_LEFT:
                return Input::EMouseButton::Left;
            case SDL_BUTTON_RIGHT:
                return Input::EMouseButton::Right;
            case SDL_BUTTON_MIDDLE:
                return Input::EMouseButton::Middle;
            default:
                return Input::EMouseButton::Unknown;
        }
    }

}