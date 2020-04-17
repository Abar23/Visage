#pragma once

#include <ostream>

namespace Visage
{
	namespace Math
	{
		class Vector2D
		{
		public:
			float x, y;

			Vector2D();
			Vector2D(float x, float y);
			Vector2D(float scalar);
			Vector2D(const Vector2D& vector);

			~Vector2D() = default;

			float Magnitude() const;
			float SqrMagnitude() const;
			Vector2D Normalize() const;
			Vector2D Negate() const;

			static float Dot(const Vector2D& leftVector, const Vector2D& rightVector);
			static Vector2D Project(const Vector2D& leftVector, const Vector2D& rightVector);
			static Vector2D Reject(const Vector2D& leftVector, const Vector2D& rightVector);
			static Vector2D Zero();
			static Vector2D XAxis();
			static Vector2D YAxis();
			static Vector2D Up();
			static Vector2D Down();
			static Vector2D Left();
			static Vector2D Right();

			Vector2D& operator=(const Vector2D& vector);
			Vector2D& operator+=(const Vector2D& vector);
			Vector2D& operator-=(const Vector2D& vector);

			Vector2D& operator*=(float scalar);
			Vector2D& operator/=(float scalar);
		};

		bool operator==(const Vector2D& leftVector, const Vector2D& rightVector);
		bool operator!=(const Vector2D& leftVector, const Vector2D& rightVector);

		Vector2D operator+(const Vector2D& leftVector, const Vector2D& rightVector);
		Vector2D operator-(const Vector2D& leftVector, const Vector2D& rightVector);

		Vector2D operator*(const Vector2D& vector, float scalar);
		Vector2D operator/(const Vector2D& vector, float scalar);

		std::ostream& operator<<(std::ostream& stream, const Vector2D& vector);
	}
}
