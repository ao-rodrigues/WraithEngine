#pragma once

#include "Core/VulkanBase.h"

namespace Wraith {
    class Window;

    class Device;

    class SwapChain;

    class Renderer {
    public:
        Renderer(Device& device, Window& window);
        ~Renderer();

        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;

        VkCommandBuffer BeginFrame();
        void BeginSwapChainRenderPass(VkCommandBuffer commandBuffer);
        void EndSwapChainRenderPass(VkCommandBuffer commandBuffer);
        void EndFrame();

        VkCommandBuffer GetCurrentCommandBuffer() const;

    private:
        void CreateCommandBuffers();
        void FreeCommandBuffers();
        void RecreateSwapChain();

        Device& _device;
        Window& _window;
        std::unique_ptr<SwapChain> _swapChain;

        std::vector<VkCommandBuffer> _commandBuffers;

        uint32_t _currentImageIndex;
        size_t _currentFrameIndex = 0;
        bool _frameStarted = false;
    };
}
