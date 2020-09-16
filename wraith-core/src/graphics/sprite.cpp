#include "Sprite.h"

namespace Wraith {
	namespace Graphics {

		Sprite::Sprite(float x, float y, float width, float height, Math::Vector4 color)
			: Renderable2D(Math::Vector3(x, y, 0), Math::Vector2(width, height), color)
		{
		}
	}
}
