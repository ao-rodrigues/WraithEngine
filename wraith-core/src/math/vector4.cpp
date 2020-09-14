#include "vector4.h"

namespace wraith {
	namespace math {
		Vector4::Vector4()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;
		}

		Vector4::Vector4(const float &x, const float &y, const float &z, const float &w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vector4 &Vector4::add(const Vector4 &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;

			return *this;
		}

		Vector4 &Vector4::subtract(const Vector4 &other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;

			return *this;
		}

		Vector4 &Vector4::multiply(const Vector4 &other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;

			return *this;
		}

		Vector4 &Vector4::divide(const Vector4 &other)
		{
			x /= other.x;
			y = other.y;
			z = other.z;
			w = other.w;

			return *this;
		}

		Vector4 operator+(Vector4 left, const Vector4 &right)
		{
			return left.add(right);
		}

		Vector4 operator-(Vector4 left, const Vector4 &right)
		{
			return left.subtract(right);
		}

		Vector4 operator*(Vector4 left, const Vector4 &right)
		{
			return left.multiply(right);
		}

		Vector4 operator/(Vector4 left, const Vector4 &right)
		{
			return left.divide(right);
		}

		bool Vector4::operator==(const Vector4 &other)
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		bool Vector4::operator!=(const Vector4 &other)
		{
			return !(*this == other);
		}

		Vector4 &Vector4::operator+=(const Vector4 &other)
		{
			return add(other);
		}

		Vector4 &Vector4::operator-=(const Vector4 &other)
		{
			return subtract(other);
		}

		Vector4 &Vector4::operator*=(const Vector4 &other)
		{
			return multiply(other);
		}

		Vector4 &Vector4::operator/=(const Vector4 &other)
		{
			return divide(other);
		}

		std::ostream &operator<<(std::ostream &stream, const Vector4 &vector)
		{
			stream << "Vector4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
		}
	}
}
