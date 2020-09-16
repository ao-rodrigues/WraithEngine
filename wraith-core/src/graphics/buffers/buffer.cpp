#include "Buffer.h"

namespace Wraith {
	namespace Graphics {

		Buffer::Buffer(GLfloat* data, GLsizei count, GLuint componentCount)
			: m_ComponentCount(componentCount)
		{
			glGenBuffers(1, &m_BufferID);
			Bind();
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
			Unbind();
		}

		Buffer::~Buffer()
		{
			glDeleteBuffers(1, &m_BufferID);
		}

		void Buffer::Bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		}

		void Buffer::Unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}

