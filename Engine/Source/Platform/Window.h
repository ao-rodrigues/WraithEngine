#pragma once

#include "Core/Core.h"
#include <string>

namespace Wraith
{
	class Window
	{
	public:
		Window() = default;
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		void Create(int width, int height, const std::string& title);

		bool ShouldClose() const
		{
			return glfwWindowShouldClose(_window);
		}

		void CreateSurface(VkInstance instance, VkSurfaceKHR* surface);

		void PollEvents();

		GLFWwindow* GetGLFWWindow()
		{
			return _window;
		}

	private:
		void InitWindow();

		int _width = 800;
		int _height = 600;
		std::string _title = "Wraith Window";
		GLFWwindow* _window = nullptr;
	};
}
