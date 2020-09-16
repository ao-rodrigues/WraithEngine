#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include "Math.h"

namespace Wraith {
	namespace Math {

		struct Matrix4
		{
			union
			{
				float values[4 * 4];
				Vector4 columns[4];
			};

			Matrix4();
			Matrix4(float diagonal);

			static Matrix4 Identity();

			Matrix4 &Multiply(const Matrix4 &other);

			friend Matrix4 operator*(Matrix4 left, const Matrix4 &right);
			Matrix4 operator*=(const Matrix4 &other);

			static Matrix4 Orthographic(float left, float right, float bottom, float top, float near, float far);
			static Matrix4 Perspective(float fov, float aspectRatio, float near, float far);

			static Matrix4 Translation(const Vector3 &translation);
			static Matrix4 Rotation(float angle, const Vector3 &axis);
			static Matrix4 Scale(const Vector3 &scale);
		};
	}
}