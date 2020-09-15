#pragma once

#include <deque>
#include "static_sprite.h"
#include "renderer_2d.h"

namespace wraith {
	namespace graphics {
		class SimpleRenderer2D : public Renderer2D
		{
		private:
			std::deque<const StaticSprite *> m_RenderQueue;

		public:
			void submit(const Renderable2D *renderable) override;
			void render() override;
		};
	}
}
