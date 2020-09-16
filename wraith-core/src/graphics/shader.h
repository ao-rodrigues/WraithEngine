#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>

#include "../utils/file_utils.h"
#include "../Math/Math.h"

namespace Wraith {
	namespace Graphics {

		class Shader
		{
		private:
			GLuint m_ProgramID;

			const char *m_VertPath;
			const char *m_FragPath;

		public:
			Shader(const char *vertPath, const char *fragPath);
			~Shader();

			void SetUniform1f(const GLchar *name, float value);
			void SetUniform2f(const GLchar *name, const Math::Vector2 &vector);
			void SetUniform3f(const GLchar *name, const Math::Vector3 &vector);
			void SetUniform4f(const GLchar *name, const Math::Vector4 &vector);

			void SetUniform1i(const GLchar *name, int value);

			void SetUniformMat4(const GLchar *name, const Math::Matrix4 &matrix);

			void Enable() const;
			void Disable() const;

		private:
			GLuint Load();
			GLint GetUniformLocation(const GLchar *name);
		};
	}
}