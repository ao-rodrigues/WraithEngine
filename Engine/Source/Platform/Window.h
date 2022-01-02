#pragma once

#include "Core/Core.h"
#include <string>

namespace Wraith
{
	class Window
	{
	public:
		Window(int width, int height, const std::string& title);
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		void CreateSurface(VkInstance instance, VkSurfaceKHR* surface);
		void PollEvents();

		GLFWwindow* GetGLFWWindow() const
		{
			return _window;
		}

		bool ShouldClose() const
		{
			return glfwWindowShouldClose(_window);
		}

		bool WindowResized() const
		{
			return _windowResized;
		}

		void ResetWindowResizedFlag()
		{
			_windowResized = false;
		}

	private:
		void InitWindow();
		static void OnFramebufferResized(GLFWwindow* window, int newWidth, int newHeight);

		int _width = 800;
		int _height = 600;
		std::string _title = "Wraith Window";
		GLFWwindow* _window = nullptr;

		bool _windowResized = false;
	};
}
