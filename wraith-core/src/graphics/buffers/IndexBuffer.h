#pragma once

#include <glad/glad.h>

namespace Wraith {
	namespace Graphics {
		class IndexBuffer
		{
		private:
			GLuint m_BufferID;
			GLuint m_Count;

		public:
			IndexBuffer(GLuint* data, GLsizei count);
			~IndexBuffer();

			void Bind() const;
			void Unbind() const;
			inline GLuint GetCount() const { return m_Count; };
		};
	}
}
