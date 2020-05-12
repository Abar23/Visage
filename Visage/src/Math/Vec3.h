#pragma once

#include <ostream>
#include "Vec2.h"

namespace Visage
{
	namespace Math
	{
		class Vec3
		{
		public:
			float x, y, z;

			Vec3();
			Vec3(const Vec3& v) = default;
			Vec3(const float x, const float y, const float z);
			Vec3(const float value);

			~Vec3() = default;

			float Magnitude() const;
			float SqrMagnitude() const;
			Vec3 Normalize() const;
			Vec3& Normalized();
			Vec3 Renormalized() const;
			Vec3& Renormalize();
			Vec3 Negated() const;
			Vec3& Negate();

			static float Dot(const Vec3& leftVector, const Vec3& rightVector);
			static Vec3 Cross(const Vec3& leftVector, const Vec3& rightVector);
			static Vec3 Project(const Vec3& leftVector, const Vec3& rightVector);
			static Vec3 Reject(const Vec3& leftVector, const Vec3& rightVector);
			static Vec3 Lerp(const Vec3& leftVector, const Vec3& rightVector, const float t);
			static Vec3 Zero();
			static Vec3 XAxis();
			static Vec3 YAxis();
			static Vec3 ZAxis();
			static Vec3 Up();
			static Vec3 Down();
			static Vec3 Left();
			static Vec3 Right();
			static Vec3 Back();
			static Vec3 Forward();

			Vec3& operator=(const Vec3& vector);
			Vec3& operator+=(const Vec3& vector);
			Vec3& operator-=(const Vec3& vector);

			Vec3& operator*=(const float scalar);
			Vec3& operator/=(const float scalar);
		};

		bool operator==(const Vec3& leftVector, const Vec3& rightVector);
		bool operator!=(const Vec3& leftVector, const Vec3& rightVector);

		Vec3 operator+(const Vec3& leftVector, const Vec3& rightVector);
		Vec3 operator-(const Vec3& leftVector, const Vec3& rightVector);

		Vec3 operator*(const Vec3& vector, const float scalar);
		Vec3 operator/(const Vec3& vector, const float scalar);

		std::ostream& operator<<(std::ostream& stream, const Vec3& vector);
	}
}

