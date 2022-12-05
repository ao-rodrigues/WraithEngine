//
// InputManager.h
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#pragma once

#include <bitset>

#include "Input.h"
#include "Singleton.h"

namespace Wraith {
    class InputManager : public Singleton<InputManager> {
    public:
        void RegisterKeyDown(Input::KeyCode keyCode);
        void RegisterKeyUp(Input::KeyCode keyCode);

        void RegisterMouseButtonDown(Input::MouseButton mouseButton);
        void RegisterMouseButtonUp(Input::MouseButton mouseButton);

        void ClearFrameEvents();

        inline bool IsKeyDown(Input::KeyCode keyCode) const;
        inline bool IsKeyUp(Input::KeyCode keyCode) const;
        inline bool IsKeyPressed(Input::KeyCode keyCode) const;

        inline bool IsMouseButtonDown(Input::MouseButton mouseButton) const;
        inline bool IsMouseButtonUp(Input::MouseButton mouseButton) const;
        inline bool IsMouseButtonPressed(Input::MouseButton mouseButton) const;

    private:
        std::bitset<static_cast<size_t>(Input::KeyCode::Count)> _keysDown;
        std::bitset<static_cast<size_t>(Input::KeyCode::Count)> _keysUp;
        std::bitset<static_cast<size_t>(Input::KeyCode::Count)> _keysPressed;

        std::bitset<static_cast<size_t>(Input::MouseButton::Count)> _mouseButtonsDown;
        std::bitset<static_cast<size_t>(Input::MouseButton::Count)> _mouseButtonsUp;
        std::bitset<static_cast<size_t>(Input::MouseButton::Count)> _mouseButtonsPressed;
    };
}