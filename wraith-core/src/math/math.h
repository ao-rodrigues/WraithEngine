#pragma once

#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"

namespace wraith {
	namespace math {
		inline float toRadians(float degrees)
		{
			return degrees * ((float)M_PI / 180.0f);
		}
	}
}

