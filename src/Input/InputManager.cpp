//
// InputManager.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#include "wrpch.h"

#include "InputManager.h"

namespace Wraith {

    void InputManager::RegisterKeyDown(Wraith::Input::EKeyCode keyCode) {
        m_KeysDown[static_cast<int>(keyCode)] = true;
        m_KeysPressed[static_cast<int>(keyCode)] = true;
    }

    void InputManager::RegisterKeyUp(Wraith::Input::EKeyCode keyCode) {
        m_KeysUp[static_cast<int>(keyCode)] = true;
        m_KeysDown[static_cast<int>(keyCode)] = false;
    }

    void InputManager::RegisterMouseButtonDown(Wraith::Input::EMouseButton mouseButton) {
        m_MouseButtonsDown[static_cast<int>(mouseButton)] = true;
        m_MouseButtonsPressed[static_cast<int>(mouseButton)] = true;
    }

    void InputManager::RegisterMouseButtonUp(Wraith::Input::EMouseButton mouseButton) {
        m_MouseButtonsUp[static_cast<int>(mouseButton)] = true;
        m_MouseButtonsDown[static_cast<int>(mouseButton)] = false;
    }

    void InputManager::RegisterMouseMotion(glm::vec2 mousePosition, glm::vec2 mouseDelta) {
        m_MousePosition = mousePosition;
        m_MouseDelta = mouseDelta;
    }

    void InputManager::RegisterMouseWheel(glm::vec2 mouseWheel) {
        m_MouseWheel = mouseWheel;
    }

    void InputManager::ClearFrameEvents() {
        m_KeysPressed.reset();
        m_KeysUp.reset();
        m_MouseButtonsPressed.reset();
        m_MouseButtonsUp.reset();
        m_MouseDelta = glm::vec2(0.0f, 0.0f);
        m_MouseWheel = glm::vec2(0.0f, 0.0f);
    }

    bool InputManager::IsKeyDown(Wraith::Input::EKeyCode keyCode) const {
        return m_KeysDown[static_cast<int>(keyCode)];
    }

    bool InputManager::IsKeyUp(Wraith::Input::EKeyCode keyCode) const {
        return m_KeysUp[static_cast<int>(keyCode)];;
    }

    bool InputManager::IsKeyPressed(Wraith::Input::EKeyCode keyCode) const {
        return m_KeysPressed[static_cast<int>(keyCode)];;
    }

    bool InputManager::IsMouseButtonDown(Wraith::Input::EMouseButton mouseButton) const {
        return m_MouseButtonsDown[static_cast<int>(mouseButton)];
    }

    bool InputManager::IsMouseButtonUp(Wraith::Input::EMouseButton mouseButton) const {
        return m_MouseButtonsUp[static_cast<int>(mouseButton)];
    }

    bool InputManager::IsMouseButtonPressed(Wraith::Input::EMouseButton mouseButton) const {
        return m_MouseButtonsPressed[static_cast<int>(mouseButton)];
    }

    glm::vec2 InputManager::GetMousePosition() const {
        return m_MousePosition;
    }

    glm::vec2 InputManager::GetMouseDelta() const {
        return m_MouseDelta;
    }

    glm::vec2 InputManager::GetMouseWheel() const {
        return m_MouseWheel;
    }

    bool Input::IsKeyDown(Wraith::Input::EKeyCode keyCode) {
        return InputManager::GetInstance().IsKeyDown(keyCode);
    }

    bool Input::IsKeyUp(Wraith::Input::EKeyCode keyCode) {
        return InputManager::GetInstance().IsKeyUp(keyCode);
    }

    bool Input::IsKeyPressed(Wraith::Input::EKeyCode keyCode) {
        return InputManager::GetInstance().IsKeyPressed(keyCode);
    }

    bool Input::IsMouseButtonDown(Wraith::Input::EMouseButton mouseButton) {
        return InputManager::GetInstance().IsMouseButtonDown(mouseButton);
    }

    bool Input::IsMouseButtonUp(Wraith::Input::EMouseButton mouseButton) {
        return InputManager::GetInstance().IsMouseButtonUp(mouseButton);
    }

    bool Input::IsMouseButtonPressed(Wraith::Input::EMouseButton mouseButton) {
        return InputManager::GetInstance().IsMouseButtonPressed(mouseButton);
    }

    glm::vec2 Input::GetMousePosition() {
        return InputManager::GetInstance().GetMousePosition();
    }

    glm::vec2 Input::GetMouseDelta() {
        return InputManager::GetInstance().GetMouseDelta();
    }

    glm::vec2 Input::GetMouseWheel() {
        return InputManager::GetInstance().GetMouseWheel();
    }

}
