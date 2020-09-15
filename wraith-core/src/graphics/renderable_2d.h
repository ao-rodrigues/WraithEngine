#pragma once

#include "buffers/buffer.h"
#include "buffers/index_buffer.h"
#include "buffers/vertex_array.h"

#include "../math/math.h"
#include "shader.h"

namespace wraith {
	namespace graphics {

		struct VertexData
		{
			math::Vector3 vertex;
			math::Vector4 color;
		};

		class Renderable2D
		{
		protected:
			math::Vector3 m_Position;
			math::Vector2 m_Size;
			math::Vector4 m_Color;

		public:
			Renderable2D(math::Vector3 position, math::Vector2 size, math::Vector4 color)
				: m_Position(position), m_Size(size), m_Color(color)
			{
				
			}

			virtual ~Renderable2D() { }

			inline const math::Vector3 &getPosition() const { return m_Position; }
			inline const math::Vector2 &getSize() const { return m_Size; }
			inline const math::Vector4 &getColor() const { return m_Color; }
		};
	}
}