//
// InputManager.h
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#pragma once

#include <bitset>

#include "Input/Input.h"
#include "Utils/Singleton.h"

namespace Wraith {
    class InputManager : public Singleton<InputManager> {
    public:
        void RegisterKeyDown(Input::KeyCode keyCode);
        void RegisterKeyUp(Input::KeyCode keyCode);

        void RegisterMouseButtonDown(Input::MouseButton mouseButton);
        void RegisterMouseButtonUp(Input::MouseButton mouseButton);

        void RegisterMouseMotion(glm::vec2 mousePosition, glm::vec2 mouseDelta);
        void RegisterMouseWheel(glm::vec2 mouseWheel);

        void ClearFrameEvents();

        inline bool IsKeyDown(Input::KeyCode keyCode) const;
        inline bool IsKeyUp(Input::KeyCode keyCode) const;
        inline bool IsKeyPressed(Input::KeyCode keyCode) const;

        inline bool IsMouseButtonDown(Input::MouseButton mouseButton) const;
        inline bool IsMouseButtonUp(Input::MouseButton mouseButton) const;
        inline bool IsMouseButtonPressed(Input::MouseButton mouseButton) const;

        inline glm::vec2 GetMousePosition() const;
        inline glm::vec2 GetMouseDelta() const;
        inline glm::vec2 GetMouseWheel() const;

    private:
        std::bitset<static_cast<size_t>(Input::KeyCode::Count)> _keysDown;
        std::bitset<static_cast<size_t>(Input::KeyCode::Count)> _keysUp;
        std::bitset<static_cast<size_t>(Input::KeyCode::Count)> _keysPressed;

        std::bitset<static_cast<size_t>(Input::MouseButton::Count)> _mouseButtonsDown;
        std::bitset<static_cast<size_t>(Input::MouseButton::Count)> _mouseButtonsUp;
        std::bitset<static_cast<size_t>(Input::MouseButton::Count)> _mouseButtonsPressed;

        glm::vec2 _mousePosition {0.0f, 0.0f};
        glm::vec2 _mouseDelta {0.0f, 0.0f};
        glm::vec2 _mouseWheel {0.0f, 0.0f};
    };
}