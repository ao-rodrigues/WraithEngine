//
// GLFWWindow.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 14/06/2022.
//

#include "GLFWWindow.h"

#include <GLFW/glfw3.h>

namespace Wraith {

    void GLFWWindow::Create(int width, int height, const std::string& title) {
        Window::Create(width, height, title);

        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(_window, this);
        glfwSetFramebufferSizeCallback(_window, OnFramebufferResized);
    }

    void GLFWWindow::Destroy() {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    void GLFWWindow::CreateSurface(VkInstance instance, VkSurfaceKHR* surface) {
        if (glfwCreateWindowSurface(instance, _window, nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create window surface!");
        }
        WR_LOG_DEBUG("Created surface.")
    }

    void GLFWWindow::GetFramebufferSize(int* width, int* height) const {
        glfwGetFramebufferSize(_window, width, height);
    }

    std::vector<const char*> GLFWWindow::GetInstanceExtensions(unsigned int* count) const {
        const char** extensionNames = glfwGetRequiredInstanceExtensions(count);
        return {extensionNames, extensionNames + *count};
    }

    void GLFWWindow::PollEvents() {
        glfwPollEvents();
    }

    void GLFWWindow::WaitEvents() {
        glfwWaitEvents();
    }

    bool GLFWWindow::ShouldClose() const {
        return glfwWindowShouldClose(_window);
    }

    void GLFWWindow::OnFramebufferResized(GLFWwindow* window, int newWidth, int newHeight) {
        const auto thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        thisWindow->_width = newWidth;
        thisWindow->_height = newHeight;
        thisWindow->_windowResized = true;
    }

}