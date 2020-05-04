#pragma once

#include <iostream>
#include "Vec3.h"
#include "Vec2.h"

namespace Visage
{
	namespace Math
	{
		class Vec4
		{
		public:
			float x, y, z, w;

			Vec4();
			Vec4(const Vec4& vector);
			Vec4(const Vec3& vector, float w);
			Vec4(const Vec2& vector, float w);
			Vec4(float x, float y, float z, float w);
			Vec4(float x, float y, float z);
			Vec4(const float scalar);

			~Vec4() = default;

			float Magnitude() const;
			float SqrMagnitude() const;
			Vec4 Normalized() const;
			Vec4& Normalize();
			Vec4 Renormalized() const;
			Vec4& Renormalize();
			Vec4 Negated() const;
			Vec4& Negate();

			static Vec4 Dot(const Vec4& leftVector, const Vec4& rightVector);
			static Vec4 Zero();

			Vec4& operator=(const Vec4& vector);
			Vec4& operator+=(const Vec4& vector);
			Vec4& operator-=(const Vec4& vector);

			Vec4& operator*=(float scalar);
			Vec4& operator/=(float scalar);
		};

		bool operator==(const Vec4& leftVector, const Vec4& rightVector);
		bool operator!=(const Vec4& leftVector, const Vec4& rightVector);

		Vec4 operator+(const Vec4& leftVector, const Vec4& rightVector);
		Vec4 operator-(const Vec4& leftVector, const Vec4& rightVector);

		Vec4 operator*(const Vec4& vector, float scalar);
		Vec4 operator/(const Vec4& vector, float scalar);

		std::ostream& operator<<(std::ostream& stream, const Vec4& vector);
	}
}
