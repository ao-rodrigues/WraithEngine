//
// Swapchain.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#include "wrpch.h"
#include "Swapchain.h"

#include "Device.h"
#include "Platform/Window.h"
#include "Core/Engine.h"
#include "VkFactory.h"

namespace Wraith {

    void Swapchain::Create(const Device& device, const Window& window) {
        _device = device;
        _window = window;

        CreateSwapchain();
        CreateImageViews();
        CreateDepthImage();
    }

    void Swapchain::Destroy() {
        vkDestroySwapchainKHR(_device->GetVkDevice(), _swapchain, nullptr);

        for (const auto imageView: _imageViews) {
            vkDestroyImageView(_device->GetVkDevice(), imageView, nullptr);
        }

        vkDestroyImageView(_device->GetVkDevice(), _depthImageView, nullptr);
        vmaDestroyImage(_device->GetAllocator(), _depthImage, _depthImageAllocation);
    }

    bool Swapchain::IsUndefined() const {
        return _swapchain == VK_NULL_HANDLE;
    }

    VkResult Swapchain::AcquireNextImage(uint32_t* imageIndex, uint64_t timeout, VkSemaphore signalSemaphore) const {
        return vkAcquireNextImageKHR(_device->GetVkDevice(), _swapchain, timeout, signalSemaphore, VK_NULL_HANDLE, imageIndex);
    }

    VkResult Swapchain::Present(VkSemaphore waitSemaphore, const uint32_t* imageIndex) {
        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = &waitSemaphore;

        const VkSwapchainKHR swapChains[] = {
                _swapchain
        };
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = imageIndex;
        presentInfo.pResults = nullptr; // Optional

        return vkQueuePresentKHR(_device->GetPresentQueue(), &presentInfo);
    }

    void Swapchain::CreateSwapchain() {
        const Device::SwapChainSupportDetails swapChainSupport = _device->GetSwapChainSupport();

        const VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
        const VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
        const VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);

        // Using the minimum means that we may sometimes have to wait on the driver to complete internal
        // operations before we can acquire another image to render to, so we add one more.
        uint32_t imageCount = std::clamp(
                swapChainSupport.capabilities.minImageCount + 1,
                swapChainSupport.capabilities.minImageCount,
                swapChainSupport.capabilities.maxImageCount);

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = _device->GetSurface();
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        const Device::QueueFamilyIndices indices = _device->GetQueueFamilyIndices();
        const uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};
        if (indices.graphicsFamily != indices.presentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0; // Optional
            createInfo.pQueueFamilyIndices = nullptr; // Optional
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(_device->GetVkDevice(), &createInfo, nullptr, &_swapchain) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create swap chain!");
        }
        WR_LOG_DEBUG("Created swap chain.");

        vkGetSwapchainImagesKHR(_device->GetVkDevice(), _swapchain, &imageCount, nullptr);
        _images.resize(imageCount);
        vkGetSwapchainImagesKHR(_device->GetVkDevice(), _swapchain, &imageCount, _images.data());

        _imageFormat = surfaceFormat.format;
        _extent = extent;
    }

    void Swapchain::CreateImageViews() {
        _imageViews.resize(_images.size());
        for (size_t i = 0; i < _images.size(); i++) {
            VkImageViewCreateInfo createInfo = VkFactory::ImageViewCreateInfo(_imageFormat, _images[i], VK_IMAGE_ASPECT_COLOR_BIT);

            if (vkCreateImageView(_device->GetVkDevice(), &createInfo, nullptr, &_imageViews[i]) != VK_SUCCESS) {
                throw std::runtime_error("Failed to create image views!");
            }
        }
        WR_LOG_DEBUG("Created image views.")
    }

    void Swapchain::CreateDepthImage() {
        _depthImageFormat = VK_FORMAT_D32_SFLOAT;
        VkExtent3D depthImageExtent = {
                _extent.width,
                _extent.height,
                1
        };
        VkImageCreateInfo imageCreateInfo = VkFactory::ImageCreateInfo(_depthImageFormat, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, depthImageExtent);

        VmaAllocationCreateInfo allocationCreateInfo{};
        allocationCreateInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;
        allocationCreateInfo.requiredFlags = VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

        vmaCreateImage(_device->GetAllocator(), &imageCreateInfo, &allocationCreateInfo, &_depthImage, &_depthImageAllocation, nullptr);

        VkImageViewCreateInfo imageViewCreateInfo = VkFactory::ImageViewCreateInfo(_depthImageFormat, _depthImage, VK_IMAGE_ASPECT_DEPTH_BIT);
        if (vkCreateImageView(_device->GetVkDevice(), &imageViewCreateInfo, nullptr, &_depthImageView) != VK_SUCCESS) {
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
            _window->GetFramebufferSize(&width, &height);

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
