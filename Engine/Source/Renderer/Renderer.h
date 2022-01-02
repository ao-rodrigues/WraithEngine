#pragma once

#include <vector>
#include <optional>

#include "Core/Singleton.h"
#include "Core/Core.h"

namespace Wraith
{
	class Window;

	class Renderer : public Singleton<Renderer>
	{
	public:
		void Init();
		void Shutdown();
		void DrawFrame();

	private:
		struct QueueFamilyIndices
		{
			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t> presentFamily;

			bool IsComplete() const
			{
				return graphicsFamily.has_value() && presentFamily.has_value();
			}
		};

		struct SwapChainSupportDetails
		{
			VkSurfaceCapabilitiesKHR capabilities{};
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};

		// Init methods
		void CreateVulkanInstance();
		void SetupDebugMessenger();
		void CreateSurface();
		void PickPhysicalDevice();
		void CreateLogicalDevice();
		void CreateSwapChain();
		void CreateImageViews();
		void CreateRenderPass();
		void CreateGraphicsPipeline();
		void CreateFramebuffers();
		void CreateCommandPool();
		void CreateCommandBuffers();
		void CreateSyncObjects();

		void CleanupSwapChain();
		void RecreateSwapChain();

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
		bool IsDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
		bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

		// Swap chain creation helpers
		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		// Shader module helpers
		VkShaderModule CreateShaderModule(const std::vector<char>& code);

#ifdef WRAITH_DEBUG
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

		static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

		VkInstance _instance = VK_NULL_HANDLE;
		VkSurfaceKHR _surface = VK_NULL_HANDLE;

		VkDebugUtilsMessengerEXT _debugMessenger = VK_NULL_HANDLE;

		VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
		VkDevice _device = VK_NULL_HANDLE;

		VkQueue _graphicsQueue = VK_NULL_HANDLE;
		VkQueue _presentQueue = VK_NULL_HANDLE;

		VkSwapchainKHR _swapChain = VK_NULL_HANDLE;
		std::vector<VkImage> _swapChainImages;
		VkFormat _swapChainImageFormat{};
		VkExtent2D _swapChainExtent{};
		std::vector<VkImageView> _swapChainImageViews;
		std::vector<VkFramebuffer> _swapChainFramebuffers;

		VkRenderPass _renderPass = VK_NULL_HANDLE;
		VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;
		VkPipeline _graphicsPipeline = VK_NULL_HANDLE;

		VkCommandPool _commandPool = VK_NULL_HANDLE;
		std::vector<VkCommandBuffer> _commandBuffers;

		std::vector<VkSemaphore> _imageAvailableSemaphores;
		std::vector<VkSemaphore> _renderFinishedSemaphores;
		std::vector<VkFence> _inFlightFences;
		std::vector<VkFence> _imagesInFlight;
		size_t _currentFrame = 0;
	};
}
