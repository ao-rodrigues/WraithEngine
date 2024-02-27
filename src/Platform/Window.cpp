//
// Window.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 07/12/2022.
//

#include "wrpch.h"

#include "Window.h"

namespace Wraith
{
    void Window::Create(int width, int height, const std::string& title)
    {
        m_Width = width;
        m_Height = height;
        m_Title = title;
    }

    VkExtent2D Window::GetExtent() const
    {
        return {static_cast<uint32_t>(m_Width), static_cast<uint32_t>(m_Height)};
    }

    bool Window::WasResized() const
    {
        return m_WindowResized;
    }

    void Window::ResetWindowResizedFlag()
    {
        m_WindowResized = false;
    }

    void Window::Destroy()
    {
    }

    void Window::CreateSurface(VkInstance instance, VkSurfaceKHR* surface)
    {
    }

    void Window::GetFramebufferSize(int* width, int* height) const
    {
    }

    std::vector<const char*> Window::GetInstanceExtensions(unsigned int* count) const
    {
        return {};
    }

    void Window::PollEvents()
    {
    }

    void Window::WaitEvents()
    {
    }

    bool Window::ShouldClose() const
    {
        return false;
    }
}
