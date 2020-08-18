#pragma once

#include "Vec2.h"

namespace Visage
{
	namespace Math
	{
		template <typename T>
		class Vec3
		{
		public:
			union
			{
				std::array<T, 3> data;
				
				struct
				{
					T x, y, z;
				};

				Swizzle<Vec2, T, 0, 0> xx;
				Swizzle<Vec2, T, 0, 1> xy;
				Swizzle<Vec2, T, 0, 2> xz;
				Swizzle<Vec2, T, 1, 0> yx;
				Swizzle<Vec2, T, 1, 1> yy;
				Swizzle<Vec2, T, 1, 2> yz;
				Swizzle<Vec2, T, 2, 0> zx;
				Swizzle<Vec2, T, 2, 1> zy;
				Swizzle<Vec2, T, 2, 2> zz;

				Swizzle<Vec3, T, 0, 0, 0> xxx;
				Swizzle<Vec3, T, 0, 0, 1> xxy;
				Swizzle<Vec3, T, 0, 0, 2> xxz;
				Swizzle<Vec3, T, 0, 1, 0> xyx;
				Swizzle<Vec3, T, 0, 1, 1> xyy;
				Swizzle<Vec3, T, 0, 1, 2> xyz;
				Swizzle<Vec3, T, 0, 2, 0> xzx;
				Swizzle<Vec3, T, 0, 2, 1> xzy;
				Swizzle<Vec3, T, 0, 2, 2> xzz;
				Swizzle<Vec3, T, 1, 0, 0> yxx;
				Swizzle<Vec3, T, 1, 0, 1> yxy;
				Swizzle<Vec3, T, 1, 0, 2> yxz;
				Swizzle<Vec3, T, 1, 1, 0> yyx;
				Swizzle<Vec3, T, 1, 1, 1> yyy;
				Swizzle<Vec3, T, 1, 1, 2> yyz;
				Swizzle<Vec3, T, 1, 2, 0> yzx;
				Swizzle<Vec3, T, 1, 2, 1> yzy;
				Swizzle<Vec3, T, 1, 2, 2> yzz;
				Swizzle<Vec3, T, 2, 0, 0> zxx;
				Swizzle<Vec3, T, 2, 0, 1> zxy;
				Swizzle<Vec3, T, 2, 0, 2> zxz;
				Swizzle<Vec3, T, 2, 1, 0> zyx;
				Swizzle<Vec3, T, 2, 1, 1> zyy;
				Swizzle<Vec3, T, 2, 1, 2> zyz;
				Swizzle<Vec3, T, 2, 2, 0> zzx;
				Swizzle<Vec3, T, 2, 2, 1> zzy;
				Swizzle<Vec3, T, 2, 2, 2> zzz;
			};

			Vec3();
			Vec3(const Vec3<T>& v) = default;
			Vec3(const T x, const T y, const T z);
			Vec3(std::initializer_list<T> args);
			Vec3(const T value);

			~Vec3() = default;

			T Magnitude() const;
			T SqrMagnitude() const;
			Vec3<T> Normalize() const;
			Vec3<T>& Normalized();
			Vec3<T> Renormalized() const;
			Vec3<T>& Renormalize();
			Vec3<T> Negated() const;
			Vec3<T>& Negate();

			static T Dot(const Vec3<T>& leftVector, const Vec3<T>& rightVector);
			static Vec3<T> Cross(const Vec3<T>& leftVector, const Vec3<T>& rightVector);
			static Vec3<T> Project(const Vec3<T>& leftVector, const Vec3<T>& rightVector);
			static Vec3<T> Reject(const Vec3<T>& leftVector, const Vec3<T>& rightVector);
			static Vec3<T> Lerp(const Vec3<T>& leftVector, const Vec3<T>& rightVector, const float t);
			static Vec3<T> Zero();
			static Vec3<T> XAxis();
			static Vec3<T> YAxis();
			static Vec3<T> ZAxis();
			static Vec3<T> Up();
			static Vec3<T> Down();
			static Vec3<T> Left();
			static Vec3<T> Right();
			static Vec3<T> Back();
			static Vec3<T> Forward();

			Vec3<T>& operator=(const Vec3<T>& vector);
			Vec3<T>& operator+=(const Vec3<T>& vector);
			Vec3<T>& operator-=(const Vec3<T>& vector);

			Vec3<T>& operator*=(const T scalar);
			Vec3<T>& operator/=(const T scalar);

			friend bool operator==(const Vec3<T>& leftVector, const Vec3<T>& rightVector)
			{
				return NearEquals(leftVector.x, rightVector.x) &&
					NearEquals(leftVector.y, rightVector.y) &&
					NearEquals(leftVector.z, rightVector.z);
			}

			friend bool operator!=(const Vec3<T>& leftVector, const Vec3<T>& rightVector)
			{
				return !(leftVector == rightVector);
			}

			friend Vec3<T> operator+(const Vec3<T>& leftVector, const Vec3<T>& rightVector)
			{
				Vec3<T> leftVectorCopy = leftVector;
				return leftVectorCopy += rightVector;
			}

			friend Vec3<T> operator-(const Vec3<T>& leftVector, const Vec3<T>& rightVector)
			{
				Vec3<T> leftVectorCopy = leftVector;
				return leftVectorCopy -= rightVector;
			}

			friend Vec3<T> operator*(const Vec3<T>& vector, const T scalar)
			{
				Vec3<T> vectorCopy = vector;
				return vectorCopy *= scalar;
			}

			friend Vec3<T> operator*(const T scalar, const Vec3<T>& vector)
			{
				Vec3<T> vectorCopy = vector;
				return vectorCopy *= scalar;
			}

			friend Vec3<T> operator/(const Vec3<T>& vector, const T scalar)
			{
				Vec3<T> vectorCopy = vector;
				return vectorCopy /= scalar;
			}

			friend Vec3<T> operator/(const T scalar, const Vec3<T>& vector)
			{
				Vec3<T> vectorCopy = vector;
				return vectorCopy /= scalar;
			}

			friend std::ostream& operator<<(std::ostream& stream, const Vec3<T>& vector)
			{
				stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
				return stream;
			}
		};
	}

	using ivec3 = Math::Vec3<int>;
	using uvec3 = Math::Vec3<unsigned int>;
	using vec3 = Math::Vec3<float>;
	using dvec3 = Math::Vec3<double>;
}

#include "Vec3.inl"
