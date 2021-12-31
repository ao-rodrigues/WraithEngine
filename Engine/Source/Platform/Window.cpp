#include "Window.h"

namespace Wraith
{
	Window::~Window()
	{
		glfwDestroyWindow(_pWindow);
		glfwTerminate();
	}

	void Window::Create(int width, int height, const std::string& title)
	{
		_width = width;
		_height = height;
		_title = title;

		InitWindow();
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::InitWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		_pWindow = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
	}
}
