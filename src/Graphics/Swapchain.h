#pragma once

#include "Core/Vulkan.h"
#include "Graphics/Device.h"
#include "Wraith/Object.h"

namespace Wraith {

    class Swapchain : public Object<Swapchain> {
    public:
        Swapchain() = default;

        void Create(const Device& device, const Window& window);
        void Destroy();

        bool IsUndefined() const override;

        VkExtent2D GetExtent() const { return _extent; }
        VkFormat GetImageFormat() const { return _imageFormat; }
        VkFormat GetDepthImageFormat() const { return _depthImageFormat; }
        const std::vector<VkImageView>& GetImageViews() const { return _imageViews; }
        VkImageView GetDepthImageView() const { return _depthImageView; }

        VkResult AcquireNextImage(uint32_t* imageIndex, uint64_t timeout, VkSemaphore signalSemaphore) const;
        VkResult Present(VkSemaphore waitSemaphore, const uint32_t* imageIndex);

    private:
        void CreateSwapchain();
        void CreateImageViews();
        void CreateDepthImage();

        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

        Device::Ref _device;
        Window::Ref _window;

        VkSwapchainKHR _swapchain = VK_NULL_HANDLE;

        std::vector<VkImage> _images;
        VkImage _depthImage{};

        VkFormat _imageFormat{};
        VkFormat _depthImageFormat{};

        VkExtent2D _extent{};
        std::vector<VkImageView> _imageViews;

        VkImageView _depthImageView{};
        VmaAllocation _depthImageAllocation = VK_NULL_HANDLE;
    };
}
