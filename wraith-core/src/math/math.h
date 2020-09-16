#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

namespace Wraith {
	namespace Math {
		inline float ToRadians(float degrees)
		{
			return degrees * ((float)M_PI / 180.0f);
		}
	}
}

