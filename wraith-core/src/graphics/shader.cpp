#include "shader.h"

namespace wraith {
	namespace graphics {

		Shader::Shader(const char *vertPath, const char *fragPath)
			: m_VertPath(vertPath), m_FragPath(fragPath)
		{
			m_ProgramID = load();
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ProgramID);
		}

		GLint Shader::getUniformLocation(const GLchar* name) 
		{
			return glGetUniformLocation(m_ProgramID, name);
		}

		void Shader::setUniform1f(const GLchar* name, float value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setUniform2f(const GLchar* name, const math::Vector2& vector)
		{
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}

		void Shader::setUniform3f(const GLchar* name, const math::Vector3& vector)
		{
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::setUniform4f(const GLchar* name, const math::Vector4& vector)
		{
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::setUniform1i(const GLchar* name, int value)
		{
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::setUniformMat4(const GLchar* name, const math::Matrix4& matrix)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.values);
		}

		GLuint Shader::load()
		{
			GLuint program = glCreateProgram();
			GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);	
			GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertSrcString = FileUtils::read_file(m_VertPath);
			std::string fragSrcString = FileUtils::read_file(m_FragPath);

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

		void Shader::enable() const
		{
			glUseProgram(m_ProgramID);
		}

		void Shader::disable() const
		{
			glUseProgram(0);
		}
	}
}
