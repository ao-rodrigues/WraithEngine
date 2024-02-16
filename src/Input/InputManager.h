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
        void RegisterKeyDown(Input::EKeyCode keyCode);
        void RegisterKeyUp(Input::EKeyCode keyCode);

        void RegisterMouseButtonDown(Input::EMouseButton mouseButton);
        void RegisterMouseButtonUp(Input::EMouseButton mouseButton);

        void RegisterMouseMotion(glm::vec2 mousePosition, glm::vec2 mouseDelta);
        void RegisterMouseWheel(glm::vec2 mouseWheel);

        void ClearFrameEvents();

        inline bool IsKeyDown(Input::EKeyCode keyCode) const;
        inline bool IsKeyUp(Input::EKeyCode keyCode) const;
        inline bool IsKeyPressed(Input::EKeyCode keyCode) const;

        inline bool IsMouseButtonDown(Input::EMouseButton mouseButton) const;
        inline bool IsMouseButtonUp(Input::EMouseButton mouseButton) const;
        inline bool IsMouseButtonPressed(Input::EMouseButton mouseButton) const;

        inline glm::vec2 GetMousePosition() const;
        inline glm::vec2 GetMouseDelta() const;
        inline glm::vec2 GetMouseWheel() const;

    private:
        std::bitset<static_cast<size_t>(Input::EKeyCode::Count)> m_KeysDown;
        std::bitset<static_cast<size_t>(Input::EKeyCode::Count)> m_KeysUp;
        std::bitset<static_cast<size_t>(Input::EKeyCode::Count)> m_KeysPressed;

        std::bitset<static_cast<size_t>(Input::EMouseButton::Count)> m_MouseButtonsDown;
        std::bitset<static_cast<size_t>(Input::EMouseButton::Count)> m_MouseButtonsUp;
        std::bitset<static_cast<size_t>(Input::EMouseButton::Count)> m_MouseButtonsPressed;

        glm::vec2 m_MousePosition {0.0f, 0.0f};
        glm::vec2 m_MouseDelta {0.0f, 0.0f};
        glm::vec2 m_MouseWheel {0.0f, 0.0f};
    };
}