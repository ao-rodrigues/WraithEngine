//
// Created by Andre Rodrigues on 14/06/2022.
//

#pragma once

#include "Window.h"

struct SDL_Window;
struct SDL_Surface;
union SDL_Event;

namespace Wraith {
    class SDL2Window : public Window {
    public:
        SDL2Window(int width, int height, const std::string& title);
        ~SDL2Window() override;

        void CreateSurface(VkInstance instance, VkSurfaceKHR* surface) override;
        void GetFramebufferSize(int* width, int* height) override;

        std::vector<const char*> GetInstanceExtensions(unsigned int* count) override;

        void WaitEvents() override;
        void PollEvents() override;
        bool ShouldClose() const override;

    private:
        void HandleEvent(SDL_Event event);

        SDL_Window* _window = nullptr;
        bool _shouldClose = false;
    };
}