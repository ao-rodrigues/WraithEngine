//
// Swapchain.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#include "wrpch.h"
#include "Swapchain.h"

#include "Graphics/Device.h"
#include "Graphics/VkFactory.h"
#include "Platform/Window.h"

namespace Wraith {

    void Swapchain::Create(const Device& device, const Window& window) {
        m_Device = device;
        m_Window = window;

        CreateSwapchain();
        CreateImageViews();
        CreateDepthImage();
    }

    void Swapchain::Destroy() {
        vkDestroySwapchainKHR(m_Device->GetVkDevice(), m_Swapchain, nullptr);

        for (const auto imageView: m_ImageViews) {
            vkDestroyImageView(m_Device->GetVkDevice(), imageView, nullptr);
        }

        vkDestroyImageView(m_Device->GetVkDevice(), m_DepthImageView, nullptr);
        vmaDestroyImage(m_Device->GetAllocator(), m_DepthImage, m_DepthImageAllocation);
    }

    bool Swapchain::IsUndefined() const {
        return m_Swapchain == VK_NULL_HANDLE;
    }

    VkResult Swapchain::AcquireNextImage(uint32_t* imageIndex, uint64_t timeout, VkSemaphore signalSemaphore) const {
        return vkAcquireNextImageKHR(m_Device->GetVkDevice(), m_Swapchain, timeout, signalSemaphore, VK_NULL_HANDLE, imageIndex);
    }

    VkResult Swapchain::Present(VkSemaphore waitSemaphore, const uint32_t* imageIndex) {
        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = &waitSemaphore;

        const VkSwapchainKHR swapChains[] = {
                m_Swapchain
        };
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = imageIndex;
        presentInfo.pResults = nullptr; // Optional

        return vkQueuePresentKHR(m_Device->GetPresentQueue(), &presentInfo);
    }

    void Swapchain::CreateSwapchain() {
        const Device::SwapChainSupportDetails swapChainSupport = m_Device->GetSwapChainSupport();

        const VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.Formats);
        const VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.PresentModes);
        const VkExtent2D extent = ChooseSwapExtent(swapChainSupport.Capabilities);

        // Using the minimum means that we may sometimes have to wait on the driver to complete internal
        // operations before we can acquire another image to render to, so we add one more.
        uint32_t imageCount = std::clamp(
                swapChainSupport.Capabilities.minImageCount + 1,
                swapChainSupport.Capabilities.minImageCount,
                swapChainSupport.Capabilities.maxImageCount);

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = m_Device->GetSurface();
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        const Device::QueueFamilyIndices indices = m_Device->GetQueueFamilyIndices();
        const uint32_t queueFamilyIndices[] = {indices.GraphicsFamily.value(), indices.PresentFamily.value()};
        if (indices.GraphicsFamily != indices.PresentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0; // Optional
            createInfo.pQueueFamilyIndices = nullptr; // Optional
        }

        createInfo.preTransform = swapChainSupport.Capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(m_Device->GetVkDevice(), &createInfo, nullptr, &m_Swapchain) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create swap chain!");
        }
        WR_LOG_DEBUG("Created swap chain.");

        vkGetSwapchainImagesKHR(m_Device->GetVkDevice(), m_Swapchain, &imageCount, nullptr);
        m_Images.resize(imageCount);
        vkGetSwapchainImagesKHR(m_Device->GetVkDevice(), m_Swapchain, &imageCount, m_Images.data());

        m_ImageFormat = surfaceFormat.format;
        m_Extent = extent;
    }

    void Swapchain::CreateImageViews() {
        m_ImageViews.resize(m_Images.size());
        for (size_t i = 0; i < m_Images.size(); i++) {
            VkImageViewCreateInfo createInfo = VkFactory::ImageViewCreateInfo(m_ImageFormat, m_Images[i], VK_IMAGE_ASPECT_COLOR_BIT);

            if (vkCreateImageView(m_Device->GetVkDevice(), &createInfo, nullptr, &m_ImageViews[i]) != VK_SUCCESS) {
                throw std::runtime_error("Failed to create image views!");
            }
        }
        WR_LOG_DEBUG("Created image views.")
    }

    void Swapchain::CreateDepthImage() {
        m_DepthImageFormat = VK_FORMAT_D32_SFLOAT;
        VkExtent3D depthImageExtent = {
                m_Extent.width,
                m_Extent.height,
                1
        };
        VkImageCreateInfo imageCreateInfo = VkFactory::ImageCreateInfo(m_DepthImageFormat, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, depthImageExtent);

        VmaAllocationCreateInfo allocationCreateInfo{};
        allocationCreateInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;
        allocationCreateInfo.requiredFlags = VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

        vmaCreateImage(m_Device->GetAllocator(), &imageCreateInfo, &allocationCreateInfo, &m_DepthImage, &m_DepthImageAllocation, nullptr);

        VkImageViewCreateInfo imageViewCreateInfo = VkFactory::ImageViewCreateInfo(m_DepthImageFormat, m_DepthImage, VK_IMAGE_ASPECT_DEPTH_BIT);
        if (vkCreateImageView(m_Device->GetVkDevice(), &imageViewCreateInfo, nullptr, &m_DepthImageView) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create depth image view!");
        }
    }

    VkSurfaceFormatKHR Swapchain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
        for (const auto& availableFormat: availableFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
                availableFormat.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR) {
                return availableFormat;
            }
        }
        return availableFormats[0];
    }

    VkPresentModeKHR Swapchain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
        for (const auto& availablePresentMode: availablePresentModes) {
            // This mode is preferred since it avoids tearing while maintaining fairly low latency
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                return availablePresentMode;
            }
        }
        // This mode also avoids tearing and is always guaranteed to be available
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D Swapchain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
        if (capabilities.currentExtent.width != UINT32_MAX) {
            return capabilities.currentExtent;
        } else {
            int width, height = 0;
            m_Window->GetFramebufferSize(&width, &height);

            VkExtent2D actualExtent = {
                    static_cast<uint32_t>(width),
                    static_cast<uint32_t>(height)
            };
            actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width,
                                            capabilities.maxImageExtent.width);
            actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height,
                                             capabilities.maxImageExtent.height);
            return actualExtent;
        }
    }

}
