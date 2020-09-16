#pragma once

#include <vector>
#include <glad/glad.h>

#include "Buffer.h"

namespace Wraith {
	namespace Graphics {
		class VertexArray
		{
		private:
			GLuint m_ArrayID;
			std::vector<Buffer*> m_Buffers;

		public:
			VertexArray();
			~VertexArray();

			void AddBuffer(Buffer *buffer, GLuint index);
			void Bind() const;
			void Unbind() const;
		};
	}
}