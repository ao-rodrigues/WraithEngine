#pragma once

#include <deque>
#include "StaticSprite.h"
#include "Renderer2D.h"

namespace Wraith {
	namespace Graphics {
		class SimpleRenderer2D : public Renderer2D
		{
		private:
			std::deque<const StaticSprite *> m_RenderQueue;

		public:
			void Submit(const Renderable2D *renderable) override;
			void Render() override;
		};
	}
}
