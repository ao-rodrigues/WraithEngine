#pragma once

#include "buffers/buffer.h"
#include "buffers/index_buffer.h"
#include "buffers/vertex_array.h"

#include "../math/math.h"
#include "shader.h"

namespace wraith {
	namespace graphics {
		class Renderable2D
		{
		protected:
			math::Vector3 m_Position;
			math::Vector2 m_Size;
			math::Vector4 m_Color;

			VertexArray *m_VertexArray;
			IndexBuffer *m_IndexBuffer;

			Shader &m_Shader;

		public:
			Renderable2D(math::Vector3 position, math::Vector2 size, math::Vector4 color, Shader &shader)
				: m_Position(position), m_Size(size), m_Color(color), m_Shader(shader)
			{
				m_VertexArray = new VertexArray();

				GLfloat vertices[] =
				{
					0, 0, 0,
					0, size.y, 0,
					size.x, size.y, 0,
					size.x, 0, 0
				};

				GLfloat colors[] =
				{
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w
				};

				m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
				m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

				GLushort indices[] =
				{
					0, 1, 2,
					2, 3, 0
				};

				m_IndexBuffer = new IndexBuffer(indices, 6);
			}

			virtual ~Renderable2D()
			{
				delete m_VertexArray;
				delete m_IndexBuffer;
			}

			inline const VertexArray *getVAO() const { return m_VertexArray; }
			inline const IndexBuffer *getIBO() const { return m_IndexBuffer; }

			inline Shader &getShader() const { return m_Shader; }

			inline const math::Vector3 &getPosition() const { return m_Position; }
			inline const math::Vector2 &getSize() const { return m_Size; }
			inline const math::Vector4 &getColor() const { return m_Color; }
		};
	}
}