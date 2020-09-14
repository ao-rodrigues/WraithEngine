#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace wraith {
	namespace graphics {

		class Window
		{
		private:
			const char *m_Title;
			int m_Width, m_Height;
			GLFWwindow *m_Window;

		public:
			Window(const char *title, int width, int height);
			~Window();
			bool closed() const;
			void update();
			void clear() const;

		private:
			bool init();
		};
	}
}
