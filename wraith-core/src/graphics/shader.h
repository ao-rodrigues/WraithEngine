#pragma once

#include <iostream>
#include <vector>
#include <GL/glew.h>

#include "../utils/file_utils.h"
#include "../math/math.h"

namespace wraith {
	namespace graphics {

		class Shader
		{
		private:
			GLuint m_ProgramID;

			const char *m_VertPath;
			const char *m_FragPath;

		public:
			Shader(const char *vertPath, const char *fragPath);
			~Shader();

			void setUniform1f(const GLchar *name, float value);
			void setUniform2f(const GLchar *name, const math::Vector2 &vector);
			void setUniform3f(const GLchar *name, const math::Vector3 &vector);
			void setUniform4f(const GLchar *name, const math::Vector4 &vector);

			void setUniform1i(const GLchar *name, int value);

			void setUniformMat4(const GLchar *name, const math::Matrix4 &matrix);

			void enable() const;
			void disable() const;

		private:
			GLuint load();
			GLint getUniformLocation(const GLchar *name);
		};
	}
}