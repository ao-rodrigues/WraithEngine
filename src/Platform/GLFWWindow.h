//
// Created by Andre Rodrigues on 14/06/2022.
//

#pragma once

#include "Window.h"

struct GLFWwindow;

namespace Wraith {
    class GLFWWindow : public Window {
    public:
        GLFWWindow(int width, int height, const std::string& title);
        ~GLFWWindow() override;

        void CreateSurface(VkInstance instance, VkSurfaceKHR *surface) override;
        void GetFramebufferSize(int *width, int *height) override;

        const char** GetInstanceExtensions(unsigned int *count) override;

        void PollEvents() override;
        void WaitEvents() override;

        bool ShouldClose() const override;

    private:
        static void OnFramebufferResized(GLFWwindow* window, int newWidth, int newHeight);

        GLFWwindow* _window = nullptr;
    };
}