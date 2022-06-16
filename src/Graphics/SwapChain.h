#pragma once

#include "Core/VulkanBase.h"

namespace Wraith {
    class Window;

    class Device;

    class SwapChain {
    public:
        explicit SwapChain(Device& device, Window& window);
        ~SwapChain();

        SwapChain(const SwapChain&) = delete;
        SwapChain& operator=(const SwapChain&) = delete;

        VkResult AcquireNextImage(uint32_t* imageIndex) const;
        VkResult SubmitCommandBuffers(const VkCommandBuffer* buffers, uint32_t* imageIndex);

        VkExtent2D GetExtent() const { return _swapChainExtent; }
        VkRenderPass GetRenderPass() const { return _renderPass; }
        VkFramebuffer GetFramebuffer(uint32_t imageIndex) const { return _swapChainFramebuffers[imageIndex]; }

        static constexpr int MAX_FRAMES_IN_FLIGHT = 2;
    private:
        void CreateSwapChain();
        void CreateImageViews();
        void CreateDepthImage();
        void CreateRenderPass();
        void CreateFramebuffers();
        void CreateSyncObjects();

        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

        Device& _device;
        Window& _window;

        VkSwapchainKHR _swapChain = VK_NULL_HANDLE;

        std::vector<VkImage> _swapChainImages;
        VkImage _depthImage{};

        VkFormat _swapChainImageFormat{};
        VkFormat _depthImageFormat{};

        VkExtent2D _swapChainExtent{};
        std::vector<VkImageView> _swapChainImageViews;
        VkImageView _depthImageView{};
        std::vector<VkFramebuffer> _swapChainFramebuffers;

        VkRenderPass _renderPass = VK_NULL_HANDLE;

        VmaAllocation _depthImageAllocation;

        std::vector<VkSemaphore> _imageAvailableSemaphores;
        std::vector<VkSemaphore> _renderFinishedSemaphores;
        std::vector<VkFence> _inFlightFences;
        std::vector<VkFence> _imagesInFlight;
        size_t _currentFrame = 0;
    };
}
