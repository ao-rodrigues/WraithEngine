#pragma once

#include <glad/glad.h>
#include "../math/Math.h"
#include "Renderable2D.h"

namespace Wraith {
	namespace Graphics {
		class Renderer2D
		{
		protected:
			virtual void Submit(const Renderable2D *renderable) = 0;
			virtual void Render() = 0;
		};
	}
}