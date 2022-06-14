//
// Created by Andre Rodrigues on 14/06/2022.
//

#pragma once

#include "Window.h"

namespace Wraith {
    class SDL2Window : public Window {
    public:
        SDL2Window(int width, int height, const std::string& title);
        ~SDL2Window() override;

        void CreateSurface(VkInstance instance, VkSurfaceKHR *surface) override;
        void GetFramebufferSize(int *width, int *height) override;

        const char** GetInstanceExtensions(unsigned int *count) override;

        void WaitEvents() override;
        void PollEvents() override;
        bool ShouldClose() const override;
    };
}