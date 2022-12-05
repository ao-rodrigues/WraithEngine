//
// SDL2Input.h
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#pragma once

#include <SDL.h>

#include "Input.h"

namespace Wraith {

    class SDL2Input {
    public:
        static Input::KeyCode TranslateKeyCode(SDL_Keycode sdlKeyCode);
        static Input::MouseButton TranslateMouseButton(Uint8 sdlMouseButton);
    };

}
