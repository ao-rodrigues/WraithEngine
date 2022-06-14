#pragma once

#include "Core/VulkanBase.h"

namespace Wraith {
	class Window {
	public:
		Window(int width, int height, const std::string& title) : _width(width), _height(height), _title(title) {}
		virtual ~Window() = default;

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		virtual void CreateSurface(VkInstance instance, VkSurfaceKHR* surface) = 0;
        virtual void GetFramebufferSize(int* width, int* height) = 0;
        virtual std::vector<const char *> GetInstanceExtensions(unsigned int* count) = 0;
		VkExtent2D GetExtent() const { return {static_cast<uint32_t>(_width), static_cast<uint32_t>(_height)}; }

		virtual void PollEvents() = 0;
        virtual void WaitEvents() = 0;
		virtual bool ShouldClose() const = 0;

		bool WasResized() const { return _windowResized; }
		void ResetWindowResizedFlag() { _windowResized = false; }

    protected:
		int _width = 800;
		int _height = 600;
		std::string _title = "Wraith Window";

		bool _windowResized = false;
	};
}
