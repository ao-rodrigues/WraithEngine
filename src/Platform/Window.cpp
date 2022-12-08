//
// Window.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 07/12/2022.
//

#include "wrpch.h"

#include "Window.h"

namespace Wraith {

    void Window::Create(int width, int height, const std::string& title) {
        _width = width;
        _height = height;
        _title = title;
    }

    VkExtent2D Window::GetExtent() const {
        return {static_cast<uint32_t>(_width), static_cast<uint32_t>(_height)};
    }

    bool Window::WasResized() const {
        return _windowResized;
    }

    void Window::ResetWindowResizedFlag() {
        _windowResized = false;
    }

    void Window::Destroy() {}

    void Window::CreateSurface(VkInstance instance, VkSurfaceKHR* surface) {}

    void Window::GetFramebufferSize(int* width, int* height) const {}

    std::vector<const char*> Window::GetInstanceExtensions(unsigned int* count) const {
        return {};
    }

    void Window::PollEvents() {}

    void Window::WaitEvents() {}

    bool Window::ShouldClose() const {
        return false;
    }

}