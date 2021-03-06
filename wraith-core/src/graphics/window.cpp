#include "Window.h"


namespace Wraith {
	namespace Graphics {

		void window_size_callback(GLFWwindow *window, int width, int height);
		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
		void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

		Window::Window(const char *title, int width, int height)
		{
			m_Title = title;
			m_Width = width;
			m_Height = height;

			if (!Init())
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

		bool Window::Init()
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

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLEW!" << std::endl;
				return false;
			}

			return true;
		}

		bool Window::KeyPressed(unsigned int keycode) const
		{
			if (keycode >= MAX_KEYS)
			{
				// TODO: Log it
				return false;
			}
			return m_KeysPressed[keycode];
		}

		bool Window::MouseButtonPressed(unsigned int button) const
		{
			if (button >= MAX_MOUSE_BUTTONS)
			{
				// TODO: Log it
				return false;
			}
			return m_MouseButtonsPressed[button];
		}

		Math::Vector2 Window::GetMousePosition() const
		{
			return Math::Vector2(m_MouseX, m_MouseY);
		}

		void Window::Clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}


		void Window::Update()
		{
			GLenum error = glGetError();

			if (error != GL_NO_ERROR)
			{
				std::cout << "OpenGL Error: " << error << std::endl;
			}

			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		bool Window::Closed() const
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

