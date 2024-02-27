//
// Window.h
// WraithEngine
//
// Created by Andre Rodrigues on 07/12/2022.
//

#pragma once

#include "Graphics/Vulkan.h"
#include "Core/Object.h"

namespace Wraith
{
    class Window : public Object<Window>
    {
    public:
        Window() = default;
        virtual ~Window() = default;

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        virtual void Create(int width, int height, const std::string& title);
        virtual void Destroy();

        virtual void CreateSurface(VkInstance instance, VkSurfaceKHR* surface);
        virtual void GetFramebufferSize(int* width, int* height) const;
        virtual std::vector<const char*> GetInstanceExtensions(unsigned int* count) const;

        VkExtent2D GetExtent() const;

        virtual void PollEvents();
        virtual void WaitEvents();
        virtual bool ShouldClose() const;

        bool WasResized() const;
        void ResetWindowResizedFlag();

    protected:
        int m_Width = 800;
        int m_Height = 600;
        std::string m_Title = "Wraith Window";

        bool m_WindowResized = false;
    };
}
