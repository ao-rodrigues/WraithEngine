#pragma once

#include "buffers/Buffer.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"

#include "../Math/Math.h"
#include "Shader.h"

namespace Wraith {
	namespace Graphics {

		struct VertexData
		{
			Math::Vector3 vertex;
			Math::Vector4 color;
		};

		class Renderable2D
		{
		protected:
			Math::Vector3 m_Position;
			Math::Vector2 m_Size;
			Math::Vector4 m_Color;

		public:
			Renderable2D(Math::Vector3 position, Math::Vector2 size, Math::Vector4 color)
				: m_Position(position), m_Size(size), m_Color(color)
			{
				
			}

			virtual ~Renderable2D() { }

			inline const Math::Vector3 &GetPosition() const { return m_Position; }
			inline const Math::Vector2 &GetSize() const { return m_Size; }
			inline const Math::Vector4 &GetColor() const { return m_Color; }
		};
	}
}