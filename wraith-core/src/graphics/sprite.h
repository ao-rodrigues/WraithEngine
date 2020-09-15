#pragma once

#include "renderable_2d.h"

namespace wraith {
	namespace graphics {
		class Sprite : public Renderable2D
		{
		public:
			Sprite(float x, float y, float width, float height, math::Vector4 color);
		};
	}
}
