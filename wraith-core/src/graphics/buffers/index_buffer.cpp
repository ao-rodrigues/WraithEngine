#include "index_buffer.h"

namespace wraith {
	namespace graphics {

		IndexBuffer::IndexBuffer(GLushort* data, GLsizei count)
			: m_Count(count)
		{
			glGenBuffers(1, &m_BufferID);
			bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
			unbind();
		}

		void IndexBuffer::bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		}

		void IndexBuffer::unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}

