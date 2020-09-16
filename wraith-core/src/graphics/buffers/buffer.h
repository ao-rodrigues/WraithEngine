#pragma once

#include <glad/glad.h>

namespace Wraith {
	namespace Graphics {
		class Buffer
		{
		private:
			GLuint m_BufferID;
			GLuint m_ComponentCount;

		public:
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
			~Buffer();

			void Bind() const;
			void Unbind() const;
			inline GLuint GetComponentCount() const { return m_ComponentCount; };
		};
	}
}
