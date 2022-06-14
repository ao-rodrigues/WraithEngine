#pragma once

#include "Core/VulkanBase.h"
#include "Platform/Window.h"

namespace Wraith {
    class Device {
    public:
        struct QueueFamilyIndices {
            std::optional<uint32_t> graphicsFamily;
            std::optional<uint32_t> presentFamily;

            bool IsComplete() const {
                return graphicsFamily.has_value() && presentFamily.has_value();
            }
        };

        struct SwapChainSupportDetails {
            VkSurfaceCapabilitiesKHR capabilities{};
            std::vector<VkSurfaceFormatKHR> formats;
            std::vector<VkPresentModeKHR> presentModes;
        };

        Device(Window& window);
        ~Device();

        Device(const Device&) = delete;
        Device& operator=(const Device&) = delete;


        VkDevice GetDevice() const { return _device; }
        VkPhysicalDevice GetPhysicalDevice() const { return _physicalDevice; }
        VkSurfaceKHR GetSurface() const { return _surface; }
        VkCommandPool GetCommandPool() const { return _primaryCommandPool; }
        VkQueue GetGraphicsQueue() const { return _graphicsQueue; }
        VkQueue GetPresentQueue() const { return _presentQueue; }
        VmaAllocator GetAllocator() const { return _allocator; }
        QueueFamilyIndices GetQueueFamilyIndices() const { return FindQueueFamilies(_physicalDevice); }
        SwapChainSupportDetails GetSwapChainSupport() const { return QuerySwapChainSupport(_physicalDevice); }

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
        void CreateCommandPools();

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
        static constexpr bool ENABLE_VALIDATION_LAYERS = true;
#else
        static constexpr bool ENABLE_VALIDATION_LAYERS = false;
#endif

        inline static const std::vector<const char*> VALIDATION_LAYERS = {
                "VK_LAYER_KHRONOS_validation"
        };
        inline static const std::vector<const char*> DEVICE_EXTENSIONS = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        Window& _window;

        VkInstance _instance = VK_NULL_HANDLE;
        VkSurfaceKHR _surface = VK_NULL_HANDLE;

        VkDebugUtilsMessengerEXT _debugMessenger = VK_NULL_HANDLE;

        VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
        VkDevice _device = VK_NULL_HANDLE;

        VkQueue _graphicsQueue = VK_NULL_HANDLE;
        VkQueue _presentQueue = VK_NULL_HANDLE;

        VkCommandPool _primaryCommandPool = VK_NULL_HANDLE;
        VkCommandPool _transientCommandPool = VK_NULL_HANDLE;

        VmaAllocator _allocator = nullptr;
    };
}
