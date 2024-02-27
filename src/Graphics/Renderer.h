//
// Renderer.h
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#pragma once

#include "Utils/Singleton.h"

#include "Graphics/Vulkan.h"

#include "Graphics/Device.h"
#include "Graphics/Swapchain.h"
#include "Graphics/Renderable.h"

#include "Platform/Window.h"

namespace Wraith
{
    class Renderer : public Singleton<Renderer>
    {
    public:
        void Init(const Device& device, Window& window);

        void RenderFrame(std::function<void(VkCommandBuffer)>&& drawRenderables);

        VkRenderPass GetRenderPass() const { return m_RenderPass; }

    private:
        struct FrameData
        {
            VkSemaphore RenderSemaphore = VK_NULL_HANDLE;
            VkSemaphore PresentSemaphore = VK_NULL_HANDLE;
            VkFence RenderFence = VK_NULL_HANDLE;

            VkCommandPool CommandPool = VK_NULL_HANDLE;
            VkCommandBuffer CommandBuffer = VK_NULL_HANDLE;
        };

        void RecreateSwapchain();
        void CreateCommandBuffers();
        void CreateRenderPass();
        void CreateFramebuffers();
        void CreateSyncStructures();

        FrameData& GetCurrentFrame();

        VkCommandBuffer BeginFrame();
        void BeginRenderPass(VkCommandBuffer commandBuffer);
        void EndRenderPass(VkCommandBuffer commandBuffer);
        void EndFrame();
        void SubmitCommandQueue();

        static constexpr int k_MaxFramesInFlight = 2;

        Device::Ref m_Device;
        Window::MutableRef m_Window;

        Swapchain m_Swapchain;

        std::vector<VkFramebuffer> m_Framebuffers;
        VkRenderPass m_RenderPass = VK_NULL_HANDLE;
        std::array<FrameData, k_MaxFramesInFlight> m_Frames;

        uint32_t m_SwapchainImageIndex = 0;
        size_t m_FrameIndex = 0;
    };
}
