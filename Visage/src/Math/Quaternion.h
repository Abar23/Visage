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
			Quaternion(float x, float y, float z, float w);
			Quaternion(const Vec3& axis, float angleInDegrees);
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
			static Quaternion MakeRotationX(float angleInDegrees);
			static Quaternion MakeRotationY(float angleInDegrees);
			static Quaternion MakeRotationZ(float angleInDegrees);
			static Quaternion MakeRotation(float angleInDegrees, const Vec3& unitVector);
			static Quaternion Lerp(const Quaternion& leftQuaternion, const Quaternion& rightQuaternion, float t);
			static Quaternion Nlerp(const Quaternion& leftQuaternion, const Quaternion& rightQuaternion, float t);
			static Quaternion Slerp(const Quaternion& leftQuaternion, const Quaternion& rightQuaternion, float t);

			Quaternion& operator=(const Quaternion& quaternion);
			Quaternion& operator*=(const Quaternion& quaterion);
			Quaternion& operator*=(float scalar);
			Quaternion& operator/=(float scalar);
			Quaternion& operator+=(const Quaternion& quaternion);
			Quaternion& operator-=(const Quaternion& quaternion);
		};

		Quaternion operator*(const Quaternion& leftQuaterion, const Quaternion& rightQuaterion);
		Vec3 operator*(const Quaternion& quaternion, const Vec3& vector);
		Quaternion operator*(const Quaternion& quaterion, float scalar);
		Quaternion operator/(const Quaternion& quaterion, float scalar);
		Quaternion operator+(const Quaternion& leftQuaterion, const Quaternion& rightQuaterion);
		Quaternion operator-(const Quaternion& leftQuaterion, const Quaternion& rightQuaterion);

		std::ostream& operator<<(std::ostream& stream, const Quaternion& quaternion);
	}
}