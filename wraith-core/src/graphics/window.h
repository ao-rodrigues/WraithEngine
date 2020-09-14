#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace wraith {
	namespace graphics {

#define MAX_KEYS 1024
#define MAX_MOUSE_BUTTONS 32

		class Window
		{
		private:
			const char *m_Title;
			int m_Width, m_Height;
			GLFWwindow *m_Window;

			bool m_KeysPressed[MAX_KEYS];
			bool m_MouseButtonsPressed[MAX_MOUSE_BUTTONS];
			double m_MouseX, m_MouseY;

		public:
			Window(const char *title, int width, int height);
			~Window();
			bool closed() const;
			void update();
			void clear() const;

			bool keyPressed(unsigned int keycode) const;
			bool mouseButtonPressed(unsigned int button) const;
			void getMousePosition(double &x, double &y) const;

		private:
			bool init();
			friend static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
			friend static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
			friend static void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos);
		};
	}
}
