#pragma once

#include "Renderable2D.h"

namespace Wraith {
	namespace Graphics {
		class StaticSprite : public Renderable2D
		{
		private:
			VertexArray *m_VertexArray;
			IndexBuffer *m_IndexBuffer;
			Shader &m_Shader;

		public:
			StaticSprite(float x, float y, float width, float height, Math::Vector4 color, Shader &shader);
			~StaticSprite();

			inline const VertexArray *GetVAO() const { return m_VertexArray; }
			inline const IndexBuffer *GetIBO() const { return m_IndexBuffer; }

			inline Shader &GetShader() const { return m_Shader; }
		};
	}
}
