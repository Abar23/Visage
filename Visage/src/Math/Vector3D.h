#pragma once

#include <ostream>
#include "Vector2D.h"

namespace Visage
{
	namespace Math
	{
		class Vector3D
		{
		public:
			float x, y, z;

			Vector3D();
			Vector3D(const Vector3D& v) = default;
			Vector3D(const Vector2D& vector);
			Vector3D(float x, float y, float z);
			Vector3D(float value);

			~Vector3D() = default;

			float Magnitude() const;
			float SqrMagnitude() const;
			Vector3D Normalize() const;
			Vector3D Negate() const;

			static float Dot(const Vector3D& leftVector, const Vector3D& rightVector);
			static Vector3D Cross(const Vector3D& leftVector, const Vector3D& rightVector);
			static Vector3D Project(const Vector3D& leftVector, const Vector3D& rightVector);
			static Vector3D Reject(const Vector3D& leftVector, const Vector3D& rightVector);
			static Vector3D Zero();
			static Vector3D XAxis();
			static Vector3D YAxis();
			static Vector3D ZAxis();
			static Vector3D Up();
			static Vector3D Down();
			static Vector3D Left();
			static Vector3D Right();
			static Vector3D Back();
			static Vector3D Forward();

			Vector3D& operator=(const Vector3D& vector);
			Vector3D& operator+=(const Vector3D& vector);
			Vector3D& operator-=(const Vector3D& vector);

			Vector3D& operator*=(float scalar);
			Vector3D& operator/=(float scalar);
		};

		bool operator==(const Vector3D& leftVector, const Vector3D& rightVector);
		bool operator!=(const Vector3D& leftVector, const Vector3D& rightVector);

		Vector3D operator+(const Vector3D& leftVector, const Vector3D& rightVector);
		Vector3D operator-(const Vector3D& leftVector, const Vector3D& rightVector);

		Vector3D operator*(const Vector3D& vector, float scalar);
		Vector3D operator/(const Vector3D& vector, float scalar);

		std::ostream& operator<<(std::ostream& stream, const Vector3D& vector);
	}
}

