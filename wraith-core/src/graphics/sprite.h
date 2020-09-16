#pragma once

#include "Renderable2D.h"

namespace Wraith {
	namespace Graphics {
		class Sprite : public Renderable2D
		{
		public:
			Sprite(float x, float y, float width, float height, Math::Vector4 color);
		};
	}
}
