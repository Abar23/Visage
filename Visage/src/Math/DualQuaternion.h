#pragma once

#include "Quaternion.h"
#include "Vector3D.h"
#include "Matrix4D.h"

namespace Visage
{
	namespace Math
	{
		class DualQuaternion
		{
		private:
			Quaternion real;
			Quaternion dual;

		public:
			DualQuaternion();
			DualQuaternion(const Quaternion& real, const Quaternion& dual);
			DualQuaternion(const Quaternion& rotation, const Vector3D& translation);
			DualQuaternion(const DualQuaternion& dualQuat);

			DualQuaternion Normalized() const;
			DualQuaternion& Normalize();
			DualQuaternion Conjugate() const;
			Matrix3D GetRotation() const;
			void SetRotation(const Matrix3D& matrix);
			Vector3D GetTranslation() const;
			void SetTranslation(const Vector3D& vector);
			Quaternion GetRealQuaternion() const; 
			void SetRealQuaternion(const Quaternion& quaternion);
			Quaternion GetDualQuaternion() const;
			void SetDaulQuaternion(const Quaternion& quaternion);
			Matrix4D ToTransformMatrix() const;

			static float Dot(const DualQuaternion& leftDualQuat, const DualQuaternion& rightDualQuat);
			static DualQuaternion Sclerp(const DualQuaternion& leftDualQuat, const DualQuaternion& rightDualQuat, float t);

			DualQuaternion& operator=(const DualQuaternion& dualQuat);
			DualQuaternion& operator*=(const DualQuaternion& dualQuat);
			DualQuaternion& operator*=(float scalar);
			DualQuaternion& operator/=(float scalar);
			DualQuaternion& operator+=(const DualQuaternion& dualQuat);
			DualQuaternion& operator-=(const DualQuaternion& dualQuat);
		};

		DualQuaternion operator*(const DualQuaternion& leftDualQuat, const DualQuaternion& rightDualQuat);
		DualQuaternion operator*(const DualQuaternion& leftDualQuat, float scalar);
		DualQuaternion operator/(const DualQuaternion& leftDualQuat, float scalar);
		DualQuaternion operator-(const DualQuaternion& leftDualQuat, const DualQuaternion& rightDualQuat);
		DualQuaternion operator+(const DualQuaternion& leftDualQuat, const DualQuaternion& rightDualQuat);
	}
}