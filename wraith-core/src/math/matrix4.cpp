#include "matrix4.h"

namespace wraith {
	namespace math {
		Matrix4::Matrix4()
		{
			std::memset(values, 0, sizeof values);
		}

		Matrix4::Matrix4(float diagonal)
		{
			std::memset(values, 0, sizeof values);

			for (int i = 0; i < 4; i++)
			{
				values[i + i * 4] = diagonal;
			}
		}

		Matrix4 Matrix4::identity()
		{
			return Matrix4(1.0f);
		}

		Matrix4 &Matrix4::multiply(const Matrix4 &other)
		{
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					float sum = 0.0f;
					for (int i = 0; i < 4; i++)
					{
						sum += values[x + i * 4] * other.values[i + y * 4];
					}

					values[x + y * 4] = sum;
				}
			}

			return *this;
		}

		Matrix4 operator*(Matrix4 left, const Matrix4 &right)
		{
			return left.multiply(right);
		}

		Matrix4 Matrix4::operator*=(const Matrix4 &other)
		{
			return multiply(other);
		}


		Matrix4 Matrix4::orthographic(float left, float right, float bottom, float top, float near, float far)
		{
			Matrix4 result = identity();

			// Diagonal
			result.values[0 + 0 * 4] = 2.0f / (right - left);
			result.values[1 + 1 * 4] = 2.0f / (top - bottom);
			result.values[2 + 2 * 4] = -2.0f / (far - near);

			// Last column
			result.values[0 + 3 * 4] = -1.0f * ((right + left) / (right - left));
			result.values[1 + 3 * 4] = -1.0f * ((top + bottom) / (top - bottom));
			result.values[2 + 3 * 4] = -1.0f * ((far + near) / (far - near));

			return result;
		}

		Matrix4 Matrix4::perspective(float fov, float aspectRatio, float near, float far)
		{
			Matrix4 result;

			float q = 1.0f / tan(toRadians(fov / 2.0f));
			float a = q / aspectRatio;
			float b = -1.0f * ((far + near) / (far - near));
			float c = -1.0f * ((2.0f * far * near) / (far - near));
			
			result.values[0 + 0 * 4] = a;
			result.values[1 + 1 * 4] = q;
			result.values[2 + 2 * 4] = b;
			result.values[3 + 2 * 4] = -1.0f;
			result.values[2 + 3 * 4] = c;

			return result;
		}

		Matrix4 Matrix4::translation(const Vector3 &translation)
		{
			Matrix4 result = identity();

			result.values[0 + 3 * 4] = translation.x;
			result.values[1 + 3 * 4] = translation.y;
			result.values[2 + 3 * 4] = translation.z;

			return result;
		}

		Matrix4 Matrix4::rotation(float angle, const Vector3 &axis)
		{
			Matrix4 result = identity();

			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.values[0 + 0 * 4] = c + x * x * omc;
			result.values[1 + 0 * 4] = y * x * omc + z * s;
			result.values[2 + 0 * 4] = z * x * omc - y * s;

			result.values[0 + 1 * 4] = x * y * omc - z * s;
			result.values[1 + 1 * 4] = c + y * y * omc;
			result.values[2 + 1 * 4] = z * y * omc + x * s;

			result.values[0 + 2 * 4] = x * z * omc + y * s;
			result.values[1 + 2 * 4] = y * z * omc - x * s;
			result.values[2 + 2 * 4] = c + z * z * omc;

			return result;
		}

		Matrix4 Matrix4::scale(const Vector3 &scale)
		{
			Matrix4 result = identity();

			result.values[0 + 0 * 4] = scale.x;
			result.values[1 + 1 * 4] = scale.y;
			result.values[2 + 2 * 4] = scale.z;

			return result;
		}
	}
}

