//
// InputManager.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#include "wrpch.h"

#include "InputManager.h"

namespace Wraith {

    void InputManager::RegisterKeyDown(Wraith::Input::KeyCode keyCode) {
        _keysDown[static_cast<int>(keyCode)] = true;
        _keysPressed[static_cast<int>(keyCode)] = true;
    }

    void InputManager::RegisterKeyUp(Wraith::Input::KeyCode keyCode) {
        _keysUp[static_cast<int>(keyCode)] = true;
        _keysDown[static_cast<int>(keyCode)] = false;
    }

    void InputManager::RegisterMouseButtonDown(Wraith::Input::MouseButton mouseButton) {
        _mouseButtonsDown[static_cast<int>(mouseButton)] = true;
        _mouseButtonsPressed[static_cast<int>(mouseButton)] = true;
    }

    void InputManager::RegisterMouseButtonUp(Wraith::Input::MouseButton mouseButton) {
        _mouseButtonsUp[static_cast<int>(mouseButton)] = true;
        _mouseButtonsDown[static_cast<int>(mouseButton)] = false;
    }

    void InputManager::RegisterMouseMotion(glm::vec2 mousePosition, glm::vec2 mouseDelta) {
        _mousePosition = mousePosition;
        _mouseDelta = mouseDelta;
    }

    void InputManager::RegisterMouseWheel(glm::vec2 mouseWheel) {
        _mouseWheel = mouseWheel;
    }

    void InputManager::ClearFrameEvents() {
        _keysPressed.reset();
        _keysUp.reset();
        _mouseButtonsPressed.reset();
        _mouseButtonsUp.reset();
        _mouseDelta = glm::vec2(0.0f, 0.0f);
        _mouseWheel = glm::vec2(0.0f, 0.0f);
    }

    bool InputManager::IsKeyDown(Wraith::Input::KeyCode keyCode) const {
        return _keysDown[static_cast<int>(keyCode)];
    }

    bool InputManager::IsKeyUp(Wraith::Input::KeyCode keyCode) const {
        return _keysUp[static_cast<int>(keyCode)];;
    }

    bool InputManager::IsKeyPressed(Wraith::Input::KeyCode keyCode) const {
        return _keysPressed[static_cast<int>(keyCode)];;
    }

    bool InputManager::IsMouseButtonDown(Wraith::Input::MouseButton mouseButton) const {
        return _mouseButtonsDown[static_cast<int>(mouseButton)];
    }

    bool InputManager::IsMouseButtonUp(Wraith::Input::MouseButton mouseButton) const {
        return _mouseButtonsUp[static_cast<int>(mouseButton)];
    }

    bool InputManager::IsMouseButtonPressed(Wraith::Input::MouseButton mouseButton) const {
        return _mouseButtonsPressed[static_cast<int>(mouseButton)];
    }

    glm::vec2 InputManager::GetMousePosition() const {
        return _mousePosition;
    }

    glm::vec2 InputManager::GetMouseDelta() const {
        return _mouseDelta;
    }

    glm::vec2 InputManager::GetMouseWheel() const {
        return _mouseWheel;
    }

    bool Input::IsKeyDown(Wraith::Input::KeyCode keyCode) {
        return InputManager::Instance().IsKeyDown(keyCode);
    }

    bool Input::IsKeyUp(Wraith::Input::KeyCode keyCode) {
        return InputManager::Instance().IsKeyUp(keyCode);
    }

    bool Input::IsKeyPressed(Wraith::Input::KeyCode keyCode) {
        return InputManager::Instance().IsKeyPressed(keyCode);
    }

    bool Input::IsMouseButtonDown(Wraith::Input::MouseButton mouseButton) {
        return InputManager::Instance().IsMouseButtonDown(mouseButton);
    }

    bool Input::IsMouseButtonUp(Wraith::Input::MouseButton mouseButton) {
        return InputManager::Instance().IsMouseButtonUp(mouseButton);
    }

    bool Input::IsMouseButtonPressed(Wraith::Input::MouseButton mouseButton) {
        return InputManager::Instance().IsMouseButtonPressed(mouseButton);
    }

    glm::vec2 Input::GetMousePosition() {
        return InputManager::Instance().GetMousePosition();
    }

    glm::vec2 Input::GetMouseDelta() {
        return InputManager::Instance().GetMouseDelta();
    }

    glm::vec2 Input::GetMouseWheel() {
        return InputManager::Instance().GetMouseWheel();
    }

}
