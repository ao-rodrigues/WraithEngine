#include "Window.h"

#include <stdexcept>

#include "Core/Logger.h"

namespace Wraith
{
	Window::Window(int width, int height, const std::string& title)
		: _width(width)
		, _height(height)
		, _title(title)
	{
		InitWindow();
	}

	Window::~Window()
	{
		glfwDestroyWindow(_window);
		glfwTerminate();
	}

	void Window::CreateSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		if (glfwCreateWindowSurface(instance, _window, nullptr, surface) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create window surface!");
		}
		LOG_DEBUG("Created surface.");
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::InitWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		_window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(_window, this);
		glfwSetFramebufferSizeCallback(_window, OnFramebufferResized);
	}

	void Window::OnFramebufferResized(GLFWwindow* window, int newWidth, int newHeight)
	{
		const auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
		thisWindow->_width = newWidth;
		thisWindow->_height = newHeight;
		thisWindow->_windowResized = true;
	}
}
