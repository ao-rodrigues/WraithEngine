#pragma once

#include "Core/VulkanBase.h"

#include "Graphics/Device.h"
#include "Graphics/Swapchain.h"
#include "Graphics/Renderable.h"

#include "Platform/Window.h"

namespace Wraith {

    class Renderer : public Singleton<Renderer> {
    public:
        void Init(const Device& device, Window& window);

        void RenderFrame(std::function<void(VkCommandBuffer)>&& drawRenderables);

        VkRenderPass GetRenderPass() const { return _renderPass; }

    private:
        struct FrameData {
            VkSemaphore renderSemaphore = VK_NULL_HANDLE;
            VkSemaphore presentSemaphore = VK_NULL_HANDLE;
            VkFence renderFence = VK_NULL_HANDLE;

            VkCommandPool commandPool = VK_NULL_HANDLE;
            VkCommandBuffer commandBuffer = VK_NULL_HANDLE;
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

        static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

        Device::Ref _device;
        Window::MutableRef _window;

        Swapchain _swapchain;

        std::vector<VkFramebuffer> _framebuffers;
        VkRenderPass _renderPass = VK_NULL_HANDLE;
        std::array<FrameData, MAX_FRAMES_IN_FLIGHT> _frames;

        uint32_t _swapChainImageIndex = 0;
        size_t _frameIndex = 0;
    };
}
