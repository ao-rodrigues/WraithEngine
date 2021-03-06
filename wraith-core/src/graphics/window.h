#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../math/Math.h"

namespace Wraith {
	namespace Graphics {

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
			bool Closed() const;
			void Update();
			void Clear() const;

			bool KeyPressed(unsigned int keycode) const;
			bool MouseButtonPressed(unsigned int button) const;
			Math::Vector2 GetMousePosition() const;

		private:
			bool Init();
			friend static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
		};
	}
}
