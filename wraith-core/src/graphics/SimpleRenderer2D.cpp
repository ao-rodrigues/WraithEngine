
#include "SimpleRenderer2D.h"

namespace Wraith {
	namespace Graphics {
		void SimpleRenderer2D::Submit(const Renderable2D *renderable)
		{
			m_RenderQueue.push_back((StaticSprite *)renderable);
		}

		void SimpleRenderer2D::Render()
		{
			while (!m_RenderQueue.empty())
			{
				const StaticSprite *sprite = m_RenderQueue.front();
				sprite->GetVAO()->Bind();
				sprite->GetIBO()->Bind();

				sprite->GetShader().SetUniformMat4("ml_matrix", Math::Matrix4::Translation(sprite->GetPosition()));
				glDrawElements(GL_TRIANGLES, sprite->GetIBO()->GetCount(), GL_UNSIGNED_INT, nullptr);

				sprite->GetVAO()->Unbind();
				sprite->GetIBO()->Unbind();

				m_RenderQueue.pop_front();
			}
		}
	}
}