//
// GLFWWindow.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 14/06/2022.
//

#include "GLFWWindow.h"

#include <GLFW/glfw3.h>

namespace Wraith
{
    void GLFWWindow::Create(int width, int height, const std::string& title)
    {
        Window::Create(width, height, title);

        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(m_Window, this);
        glfwSetFramebufferSizeCallback(m_Window, OnFramebufferResized);
    }

    void GLFWWindow::Destroy()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void GLFWWindow::CreateSurface(VkInstance instance, VkSurfaceKHR* surface)
    {
        if (glfwCreateWindowSurface(instance, m_Window, nullptr, surface) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create window surface!");
        }
        WR_LOG_DEBUG("Created surface.")
    }

    void GLFWWindow::GetFramebufferSize(int* width, int* height) const
    {
        glfwGetFramebufferSize(m_Window, width, height);
    }

    std::vector<const char*> GLFWWindow::GetInstanceExtensions(unsigned int* count) const
    {
        const char** extensionNames = glfwGetRequiredInstanceExtensions(count);
        return {extensionNames, extensionNames + *count};
    }

    void GLFWWindow::PollEvents()
    {
        glfwPollEvents();
    }

    void GLFWWindow::WaitEvents()
    {
        glfwWaitEvents();
    }

    bool GLFWWindow::ShouldClose() const
    {
        return glfwWindowShouldClose(m_Window);
    }

    void GLFWWindow::OnFramebufferResized(GLFWwindow* window, int newWidth, int newHeight)
    {
        const auto thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        thisWindow->m_Width = newWidth;
        thisWindow->m_Height = newHeight;
        thisWindow->m_WindowResized = true;
    }
}
