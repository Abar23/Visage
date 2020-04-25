#pragma once

#include "Vector3D.h"
#include "Matrix3D.h"

namespace Visage
{
	namespace Math
	{
		class Quaternion
		{
		public:
			float x, y, z, w;

			Quaternion();
			Quaternion(float axisX, float axisY, float axisZ, float anlgeInDegrees);
			Quaternion(const Vector3D& axis, float angleInDegrees);
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
			Matrix3D GetRotationMatrix() const;
			void SetRotationMatrix(const Matrix3D& matrix);

			static Vector3D TransformVector(const Quaternion& quaterion, const Vector3D& vector);
			static float Dot(const Quaternion& leftQuaterion, const Quaternion& rightQuaterion);
			static Quaternion MakeRotationX(float angleInDegrees);
			static Quaternion MakeRotationY(float angleInDegrees);
			static Quaternion MakeRotationZ(float angleInDegrees);
			static Quaternion MakeRotation(float angleInDegrees, const Vector3D& unitVector);
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
		Quaternion operator*(const Quaternion& quaterion, float scalar);
		Quaternion operator/(const Quaternion& quaterion, float scalar);
		Quaternion operator+(const Quaternion& leftQuaterion, const Quaternion& rightQuaterion);
		Quaternion operator-(const Quaternion& leftQuaterion, const Quaternion& rightQuaterion);

		std::ostream& operator<<(std::ostream& stream, const Quaternion& quaternion);
	}
}