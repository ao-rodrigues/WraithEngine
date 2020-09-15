
#include "simple_renderer_2d.h"

namespace wraith {
	namespace graphics {
		void SimpleRenderer2D::submit(const Renderable2D *renderable)
		{
			m_RenderQueue.push_back((StaticSprite *)renderable);
		}

		void SimpleRenderer2D::render()
		{
			while (!m_RenderQueue.empty())
			{
				const StaticSprite *sprite = m_RenderQueue.front();
				sprite->getVAO()->bind();
				sprite->getIBO()->bind();

				sprite->getShader().setUniformMat4("ml_matrix", math::Matrix4::translation(sprite->getPosition()));
				glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

				sprite->getVAO()->unbind();
				sprite->getIBO()->unbind();

				m_RenderQueue.pop_front();
			}
		}
	}
}