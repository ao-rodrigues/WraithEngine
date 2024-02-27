//
// SDL2Window.h
// WraithEngine
//
// Created by Andre Rodrigues on 14/06/2022.
//

#pragma once

#include "Platform/Window.h"

struct SDL_Window;
union SDL_Event;

namespace Wraith
{
    class SDL2Window : public Window
    {
    public:
        void Create(int width, int height, const std::string& title) override;
        void Destroy() override;

        void CreateSurface(VkInstance instance, VkSurfaceKHR* surface) override;
        void GetFramebufferSize(int* width, int* height) const override;

        std::vector<const char*> GetInstanceExtensions(unsigned int* count) const override;

        void WaitEvents() override;
        void PollEvents() override;
        bool ShouldClose() const override;

    private:
        void HandleEvent(SDL_Event event);
        void HandleInputEvent(SDL_Event event);

        SDL_Window* m_Window = nullptr;
        bool m_ShouldClose = false;
    };
}
