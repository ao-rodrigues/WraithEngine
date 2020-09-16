#include "Shader.h"

namespace Wraith {
	namespace Graphics {

		Shader::Shader(const char *vertPath, const char *fragPath)
			: m_VertPath(vertPath), m_FragPath(fragPath)
		{
			m_ProgramID = Load();
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ProgramID);
		}

		GLint Shader::GetUniformLocation(const GLchar* name) 
		{
			return glGetUniformLocation(m_ProgramID, name);
		}

		void Shader::SetUniform1f(const GLchar* name, float value)
		{
			glUniform1f(GetUniformLocation(name), value);
		}

		void Shader::SetUniform2f(const GLchar* name, const Math::Vector2& vector)
		{
			glUniform2f(GetUniformLocation(name), vector.x, vector.y);
		}

		void Shader::SetUniform3f(const GLchar* name, const Math::Vector3& vector)
		{
			glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::SetUniform4f(const GLchar* name, const Math::Vector4& vector)
		{
			glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::SetUniform1i(const GLchar* name, int value)
		{
			glUniform1i(GetUniformLocation(name), value);
		}

		void Shader::SetUniformMat4(const GLchar* name, const Math::Matrix4& matrix)
		{
			glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.values);
		}

		GLuint Shader::Load()
		{
			GLuint program = glCreateProgram();
			GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);	
			GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertSrcString = FileUtils::ReadFile(m_VertPath);
			std::string fragSrcString = FileUtils::ReadFile(m_FragPath);

			const char* vertSrc = vertSrcString.c_str();
			const char *fragSrc = fragSrcString.c_str();

			glShaderSource(vertShader, 1, &vertSrc, NULL);
			glCompileShader(vertShader);

			GLint compileResult;
			glGetShaderiv(vertShader, GL_COMPILE_STATUS, &compileResult);

			if (compileResult == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertShader, length, &length, &error[0]);
				std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;

				glDeleteShader(vertShader);
				return 0;
			}

			glShaderSource(fragShader, 1, &fragSrc, NULL);
			glCompileShader(fragShader);

			glGetShaderiv(fragShader, GL_COMPILE_STATUS, &compileResult);

			if (compileResult == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragShader, length, &length, &error[0]);
				std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;

				glDeleteShader(fragShader);
				return 0;
			}

			glAttachShader(program, vertShader);
			glAttachShader(program, fragShader);

			glLinkProgram(program);
			glValidateProgram(program);


			glDeleteShader(vertShader);
			glDeleteShader(fragShader);

			return program;
		}

		void Shader::Enable() const
		{
			glUseProgram(m_ProgramID);
		}

		void Shader::Disable() const
		{
			glUseProgram(0);
		}
	}
}
