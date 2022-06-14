//
// Created by Andre Rodrigues on 14/06/2022.
//

#include "SDL2Window.h"

#include <SDL.h>
#include <SDL_vulkan.h>

namespace Wraith {

    SDL2Window::SDL2Window(int width, int height, const std::string& title) : Window(width, height, title) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            WR_LOG_ERROR("SDL init failed! Error: %s", SDL_GetError());
        } else {
            _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                                       SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
            if (_window == nullptr) {
                WR_LOG_ERROR("SDL Window creation failed! Error: %s", SDL_GetError());
            }
        }
    }

    SDL2Window::~SDL2Window() {
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }

    void SDL2Window::CreateSurface(VkInstance instance, VkSurfaceKHR* surface) {
        SDL_Vulkan_CreateSurface(_window, instance, surface);
    }

    void SDL2Window::GetFramebufferSize(int* width, int* height) {
        SDL_Vulkan_GetDrawableSize(_window, width, height);
    }

    std::vector<const char*> SDL2Window::GetInstanceExtensions(unsigned int* count) {
        if (!SDL_Vulkan_GetInstanceExtensions(_window, count, nullptr)) {
            WR_LOG_ERROR("SDL: Failed to get instance extensions!");
        }

        std::vector<const char*> extensions(*count);

        if (!SDL_Vulkan_GetInstanceExtensions(_window, count, extensions.data())) {
            WR_LOG_ERROR("SDL: Failed to get instance extensions!");
        }
        return extensions;
    }

    void SDL2Window::PollEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            HandleEvent(event);
        }
    }

    void SDL2Window::WaitEvents() {
        SDL_Event event;
        while (SDL_WaitEvent(&event)) {
            HandleEvent(event);
        }
    }

    bool SDL2Window::ShouldClose() const {
        return _shouldClose;
    }

    void SDL2Window::HandleEvent(SDL_Event event) {
        if (event.type == SDL_QUIT) {
            _shouldClose = true;
        } else if (event.type == SDL_WINDOWEVENT) {
            switch (event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    _width = event.window.data1;
                    _height = event.window.data2;
                    _windowResized = true;
                    break;
                default:
                    // TODO handle other window events
                    break;
            }
        }
    }
}