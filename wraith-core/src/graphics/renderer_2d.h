#pragma once

#include <GL/glew.h>
#include "../math/math.h"
#include "renderable_2d.h"

namespace wraith {
	namespace graphics {
		class Renderer2D
		{
		protected:
			virtual void submit(const Renderable2D *renderable) = 0;
			virtual void render() = 0;
		};
	}
}