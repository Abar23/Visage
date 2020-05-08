#pragma once

#include <ostream>

namespace Visage
{
	namespace Math
	{
		class Vec2
		{
		public:
			float x, y;

			Vec2();
			Vec2(float x, float y);
			Vec2(float scalar);
			Vec2(const Vec2& vector);

			~Vec2() = default;

			float Magnitude() const;
			float SqrMagnitude() const;
			Vec2 Normalized() const;
			Vec2& Normalize();
			Vec2 Renormalized() const;
			Vec2& Renormalize();
			Vec2 Negated() const;
			Vec2& Negate();

			static float Dot(const Vec2& leftVector, const Vec2& rightVector);
			static Vec2 Project(const Vec2& leftVector, const Vec2& rightVector);
			static Vec2 Reject(const Vec2& leftVector, const Vec2& rightVector);
			static Vec2 Lerp(const Vec2& leftVector, const Vec2& rightVector, float t);
			static Vec2 Zero();
			static Vec2 XAxis();
			static Vec2 YAxis();
			static Vec2 Up();
			static Vec2 Down();
			static Vec2 Left();
			static Vec2 Right();

			Vec2& operator=(const Vec2& vector);
			Vec2& operator+=(const Vec2& vector);
			Vec2& operator-=(const Vec2& vector);

			Vec2& operator*=(float scalar);
			Vec2& operator/=(float scalar);
		};

		bool operator==(const Vec2& leftVector, const Vec2& rightVector);
		bool operator!=(const Vec2& leftVector, const Vec2& rightVector);

		Vec2 operator+(const Vec2& leftVector, const Vec2& rightVector);
		Vec2 operator-(const Vec2& leftVector, const Vec2& rightVector);

		Vec2 operator*(const Vec2& vector, float scalar);
		Vec2 operator/(const Vec2& vector, float scalar);

		std::ostream& operator<<(std::ostream& stream, const Vec2& vector);
	}
}
