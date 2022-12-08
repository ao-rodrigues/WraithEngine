#pragma once

#include "Core/VulkanBase.h"
#include "Graphics/Device.h"
#include "Wraith/Object.h"

namespace Wraith {

    class SwapChain : public Object<SwapChain> {
    public:
        SwapChain() = default;

        void Create(const Device& device, const Window& window);
        void Destroy();

        bool IsUndefined() const override;

        VkExtent2D GetExtent() const { return _swapChainExtent; }
        VkFormat GetImageFormat() const { return _swapChainImageFormat; }
        VkFormat GetDepthImageFormat() const { return _depthImageFormat; }
        const std::vector<VkImageView>& GetImageViews() const { return _swapChainImageViews; }
        VkImageView GetDepthImageView() const { return _depthImageView; }

        VkResult AcquireNextImage(uint32_t* imageIndex, uint64_t timeout, VkSemaphore signalSemaphore) const;
        VkResult Present(VkSemaphore waitSemaphore, const uint32_t* imageIndex);

    private:
        void CreateSwapChain();
        void CreateImageViews();
        void CreateDepthImage();

        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

        Device::Ref _device;
        Window::Ref _window;

        VkSwapchainKHR _swapChain = VK_NULL_HANDLE;

        std::vector<VkImage> _swapChainImages;
        VkImage _depthImage{};

        VkFormat _swapChainImageFormat{};
        VkFormat _depthImageFormat{};

        VkExtent2D _swapChainExtent{};
        std::vector<VkImageView> _swapChainImageViews;

        VkImageView _depthImageView{};
        VmaAllocation _depthImageAllocation = VK_NULL_HANDLE;
    };
}
