//
// GLFWWindow.h
// WraithEngine
//
// Created by Andre Rodrigues on 14/06/2022.
//

#pragma once

#include "Platform/Window.h"

struct GLFWwindow;

namespace Wraith {
    class GLFWWindow : public Window {
    public:
        void Create(int width, int height, const std::string& title) override;
        void Destroy() override;

        void CreateSurface(VkInstance instance, VkSurfaceKHR* surface) override;
        void GetFramebufferSize(int* width, int* height) const override;

        std::vector<const char*> GetInstanceExtensions(unsigned int* count) const override;

        void PollEvents() override;
        void WaitEvents() override;

        bool ShouldClose() const override;

    private:
        static void OnFramebufferResized(GLFWwindow* window, int newWidth, int newHeight);

        GLFWwindow* m_Window = nullptr;
    };
}