#include "sprite.h"

namespace wraith {
	namespace graphics {

		Sprite::Sprite(float x, float y, float width, float height, math::Vector4 color)
			: Renderable2D(math::Vector3(x, y, 0), math::Vector2(width, height), color)
		{
		}
	}
}
