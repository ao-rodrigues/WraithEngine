#pragma once

#include <iostream>

namespace wraith {
	namespace math {
		struct Vector4
		{
			float x, y, z, w;

			Vector4();
			Vector4(const float &x, const float &y, const float &z, const float &w);

			Vector4 &add(const Vector4 &other);
			Vector4 &subtract(const Vector4 &other);
			Vector4 &multiply(const Vector4 &other);
			Vector4 &divide(const Vector4 &other);

			friend Vector4 operator+(Vector4 left, const Vector4 &right);
			friend Vector4 operator-(Vector4 left, const Vector4 &right);
			friend Vector4 operator*(Vector4 left, const Vector4 &right);
			friend Vector4 operator/(Vector4 left, const Vector4 &right);

			bool operator==(const Vector4 &other);
			bool operator!=(const Vector4 &other);

			Vector4 &operator+=(const Vector4 &other);
			Vector4 &operator-=(const Vector4 &other);
			Vector4 &operator*=(const Vector4 &other);
			Vector4 &operator/=(const Vector4 &other);

			friend std::ostream &operator<<(std::ostream &stream, const Vector4 &vector);
		};
	}
}