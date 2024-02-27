//
// Device.h
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#pragma once

#include "Core/Object.h"
#include "Graphics/Vulkan.h"
#include "Platform/Window.h"

namespace Wraith
{
    class Device : public Object<Device>
    {
    public:
        struct QueueFamilyIndices
        {
            std::optional<uint32_t> GraphicsFamily;
            std::optional<uint32_t> PresentFamily;

            bool IsComplete() const
            {
                return GraphicsFamily.has_value() && PresentFamily.has_value();
            }
        };

        struct SwapChainSupportDetails
        {
            VkSurfaceCapabilitiesKHR Capabilities {};
            std::vector<VkSurfaceFormatKHR> Formats;
            std::vector<VkPresentModeKHR> PresentModes;
        };

        Device() = default;

        void Create(Window& window);
        void Destroy();

        bool IsUndefined() const override;

        VkDevice GetVkDevice() const { return m_Device; }
        VkPhysicalDevice GetPhysicalDevice() const { return m_PhysicalDevice; }
        VkSurfaceKHR GetSurface() const { return m_Surface; }
        VkQueue GetGraphicsQueue() const { return m_GraphicsQueue; }
        VkQueue GetPresentQueue() const { return m_PresentQueue; }
        VmaAllocator GetAllocator() const { return m_Allocator; }
        QueueFamilyIndices GetQueueFamilyIndices() const { return FindQueueFamilies(m_PhysicalDevice); }
        SwapChainSupportDetails GetSwapChainSupport() const { return QuerySwapChainSupport(m_PhysicalDevice); }

        VkCommandPool CreateCommandPool() const;

        void FinishOperations() const;

        // Buffer helper functions
        void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer, VmaMemoryUsage memoryUsage,
                          VmaAllocation& allocation);
        void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    private:
        // Init methods
        void CreateInstance();
        void SetupDebugMessenger();
        void CreateSurface();
        void PickPhysicalDevice();
        void CreateLogicalDevice();
        void CreateAllocator();

        // Validation layer setup helpers
        bool CheckValidationLayerSupport();
        std::vector<const char*> GetRequiredInstanceExtensions();
        void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
            void* userData
        );

        // Device creation helpers
        bool IsDeviceSuitable(VkPhysicalDevice device) const;
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device) const;
        bool CheckDeviceExtensionSupport(VkPhysicalDevice device) const;
        SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device) const;

        uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const;


#ifdef WR_LOG_DEBUG
        static constexpr bool k_EnableValidationLayers = true;
#else
        static constexpr bool k_EnableValidationLayers = false;
#endif

        inline static const std::vector<const char*> k_ValidationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };
        inline static const std::vector<const char*> k_DeviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        Window::MutableRef m_Window;

        VkInstance m_Instance = VK_NULL_HANDLE;
        VkSurfaceKHR m_Surface = VK_NULL_HANDLE;

        VkDebugUtilsMessengerEXT m_DebugMessenger = VK_NULL_HANDLE;

        VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
        VkDevice m_Device = VK_NULL_HANDLE;

        VkQueue m_GraphicsQueue = VK_NULL_HANDLE;
        VkQueue m_PresentQueue = VK_NULL_HANDLE;

        VmaAllocator m_Allocator = nullptr;
    };
}
