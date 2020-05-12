#pragma once

#include "Vec3.h"
#include "Mat3.h"

namespace Visage
{
	namespace Math
	{
		class Quaternion
		{
		public:
			float x, y, z, w;

			Quaternion();
			Quaternion(const float x, const float y, const float z, const float w);
			Quaternion(const Vec3& unitVector, const float angleInDegrees);
			Quaternion(const Quaternion& quaternion);

			~Quaternion() = default;

			float Norm() const;
			float SqrNorm() const;
			Quaternion Normalized() const;
			Quaternion& Normalize();
			Quaternion Renormalized() const;
			Quaternion& Renormalize();
			Quaternion Inverted() const;
			Quaternion& Invert();
			Quaternion Conjugate() const;
			Mat3 GetRotationMatrix() const;
			void SetRotationMatrix(const Mat3& matrix);

			static Vec3 TransformVector(const Quaternion& quaterion, const Vec3& vector);
			static float Dot(const Quaternion& leftQuaterion, const Quaternion& rightQuaterion);
			static Quaternion MakeRotationX(const float angleInDegrees);
			static Quaternion MakeRotationY(const float angleInDegrees);
			static Quaternion MakeRotationZ(const float angleInDegrees);
			static Quaternion MakeRotation(const Vec3& unitVector, const float angleInDegrees);
			static Quaternion Lerp(const Quaternion& leftQuaternion, const Quaternion& rightQuaternion, const float t);
			static Quaternion Nlerp(const Quaternion& leftQuaternion, const Quaternion& rightQuaternion, const float t);
			static Quaternion Slerp(const Quaternion& leftQuaternion, const Quaternion& rightQuaternion, const float t);

			Quaternion& operator=(const Quaternion& quaternion);
			Quaternion& operator*=(const Quaternion& quaterion);
			Quaternion& operator*=(const float scalar);
			Quaternion& operator/=(const float scalar);
			Quaternion& operator+=(const Quaternion& quaternion);
			Quaternion& operator-=(const Quaternion& quaternion);
		};

		Quaternion operator*(const Quaternion& leftQuaterion, const Quaternion& rightQuaterion);
		Vec3 operator*(const Quaternion& quaternion, const Vec3& vector);
		Quaternion operator*(const Quaternion& quaterion, const float scalar);
		Quaternion operator/(const Quaternion& quaterion, const float scalar);
		Quaternion operator+(const Quaternion& leftQuaterion, const Quaternion& rightQuaterion);
		Quaternion operator-(const Quaternion& leftQuaterion, const Quaternion& rightQuaterion);

		std::ostream& operator<<(std::ostream& stream, const Quaternion& quaternion);
	}
}