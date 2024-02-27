//
// SDL2Input.h
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#pragma once

#include <SDL2/SDL.h>

#include "Input/Input.h"

namespace Wraith
{
    class SDL2Input
    {
    public:
        static Input::EKeyCode TranslateKeyCode(SDL_Keycode sdlKeyCode);
        static Input::EMouseButton TranslateMouseButton(Uint8 sdlMouseButton);
    };
}
