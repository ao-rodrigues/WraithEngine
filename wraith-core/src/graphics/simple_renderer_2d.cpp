
#include "simple_renderer_2d.h"

namespace wraith {
	namespace graphics {
		void SimpleRenderer2D::submit(const Renderable2D *renderable)
		{
			m_RenderQueue.push_back(renderable);
		}

		void SimpleRenderer2D::flush()
		{
			while (!m_RenderQueue.empty())
			{
				const Renderable2D *renderable = m_RenderQueue.front();
				renderable->getVAO()->bind();
				renderable->getIBO()->bind();

				renderable->getShader().setUniformMat4("ml_matrix", math::Matrix4::translation(renderable->getPosition()));
				glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

				renderable->getVAO()->unbind();
				renderable->getIBO()->unbind();

				m_RenderQueue.pop_front();
			}
		}
	}
}