#include "window.h"

namespace wraith {
	namespace graphics {

		void window_size_callback(GLFWwindow *window, int width, int height);
		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
		void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

		Window::Window(const char *title, int width, int height)
		{
			m_Title = title;
			m_Width = width;
			m_Height = height;

			if (!init())
			{
				glfwTerminate();
			}

			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_KeysPressed[i] = false;
			}
			
			for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
			{
				m_MouseButtonsPressed[i] = false;
			}
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::init()
		{
			if (!glfwInit())
			{
				std::cout << "Failed to initialize GLFW!" << std::endl;
				return false;
			}

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

			if (!m_Window)
			{
				std::cout << "Failed to create GLFW window!" << std::endl;
				return false;
			}

			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, window_size_callback);

			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);

			if (glewInit() != GLEW_OK)
			{
				std::cout << "Failed to initialize GLEW!" << std::endl;
				return false;
			}

			return true;
		}

		bool Window::keyPressed(unsigned int keycode) const
		{
			if (keycode >= MAX_KEYS)
			{
				// TODO: Log it
				return false;
			}
			return m_KeysPressed[keycode];
		}

		bool Window::mouseButtonPressed(unsigned int button) const
		{
			if (button >= MAX_MOUSE_BUTTONS)
			{
				// TODO: Log it
				return false;
			}
			return m_MouseButtonsPressed[button];
		}

		void Window::getMousePosition(double &x, double &y) const
		{
			x = m_MouseX;
			y = m_MouseY;
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}


		void Window::update()
		{
			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void window_size_callback(GLFWwindow *window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
		
		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			Window *windowInstance = (Window *)glfwGetWindowUserPointer(window);
			windowInstance->m_KeysPressed[key] = action != GLFW_RELEASE;
		}

		void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
		{
			Window *windowInstance = (Window *)glfwGetWindowUserPointer(window);
			windowInstance->m_MouseButtonsPressed[button] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
		{
			Window *windowInstance = (Window *)glfwGetWindowUserPointer(window);
			windowInstance->m_MouseX = xpos;
			windowInstance->m_MouseY = ypos;
		}
	}
}

