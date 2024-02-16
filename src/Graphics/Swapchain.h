//
// Swapchain.h
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#pragma once

#include "Graphics/Vulkan.h"
#include "Graphics/Device.h"
#include "Core/Object.h"

namespace Wraith {

    class Swapchain : public Object<Swapchain> {
    public:
        Swapchain() = default;

        void Create(const Device& device, const Window& window);
        void Destroy();

        bool IsUndefined() const override;

        VkExtent2D GetExtent() const { return m_Extent; }
        VkFormat GetImageFormat() const { return m_ImageFormat; }
        VkFormat GetDepthImageFormat() const { return m_DepthImageFormat; }
        const std::vector<VkImageView>& GetImageViews() const { return m_ImageViews; }
        VkImageView GetDepthImageView() const { return m_DepthImageView; }

        VkResult AcquireNextImage(uint32_t* imageIndex, uint64_t timeout, VkSemaphore signalSemaphore) const;
        VkResult Present(VkSemaphore waitSemaphore, const uint32_t* imageIndex);

    private:
        void CreateSwapchain();
        void CreateImageViews();
        void CreateDepthImage();

        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

        Device::Ref m_Device;
        Window::Ref m_Window;

        VkSwapchainKHR m_Swapchain = VK_NULL_HANDLE;

        std::vector<VkImage> m_Images;
        VkImage m_DepthImage{};

        VkFormat m_ImageFormat{};
        VkFormat m_DepthImageFormat{};

        VkExtent2D m_Extent{};
        std::vector<VkImageView> m_ImageViews;

        VkImageView m_DepthImageView{};
        VmaAllocation m_DepthImageAllocation = VK_NULL_HANDLE;
    };
}
