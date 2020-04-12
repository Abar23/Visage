#pragma once

#include <iostream>
#include "Vector3D.h"

namespace Visage
{
	namespace Math
	{
		class Vector4D
		{
		public:
			float x, y, z, w;

			Vector4D();
			Vector4D(const Vector4D& vector);
			Vector4D(const Vector3D& vector);
			Vector4D(float x, float y, float z, float w);
			Vector4D(float x, float y, float z);
			Vector4D(const float scalar);

			~Vector4D() = default;

			float Magnitude() const;
			float SqrMagnitude() const;
			Vector4D Normalize() const;
			Vector4D Negate() const;
			static Vector4D Dot(const Vector4D& leftVector, const Vector4D& rightVector);

			static Vector3D Zero();

			Vector4D& operator=(const Vector4D& vector);
			Vector4D& operator+=(const Vector4D& vector);
			Vector4D& operator-=(const Vector4D& vector);

			Vector4D& operator*=(const float scalar);
			Vector4D& operator/=(const float scalar);
		};

		bool operator==(const Vector4D& leftVector, const Vector4D& rightVector);
		bool operator!=(const Vector4D& leftVector, const Vector4D& rightVector);

		Vector4D operator+(const Vector4D& leftVector, const Vector4D& rightVector);
		Vector4D operator-(const Vector4D& leftVector, const Vector4D& rightVector);

		Vector4D operator*(const Vector4D& vector, float scalar);
		Vector4D operator/(const Vector4D& vector, float scalar);

		std::ostream& operator<<(std::ostream& stream, const Vector4D& vector);
	}
}
