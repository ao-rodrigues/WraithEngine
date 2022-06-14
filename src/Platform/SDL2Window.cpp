//
// Created by Andre Rodrigues on 14/06/2022.
//

#include "SDL2Window.h"

namespace Wraith {

    SDL2Window::SDL2Window(int width, int height, const std::string &title) : Window(width, height, title) {

    }

    SDL2Window::~SDL2Window() {

    }

    void SDL2Window::CreateSurface(VkInstance instance, VkSurfaceKHR *surface) {

    }

    void SDL2Window::GetFramebufferSize(int *width, int *height) {

    }

    const char** SDL2Window::GetInstanceExtensions(unsigned int *count) {
        return nullptr;
    }

    void SDL2Window::PollEvents() {

    }

    void SDL2Window::WaitEvents() {

    }

    bool SDL2Window::ShouldClose() const {
        return false;
    }
}