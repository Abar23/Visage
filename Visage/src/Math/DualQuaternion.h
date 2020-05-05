#pragma once

#include "Quaternion.h"
#include "Vec3.h"
#include "Mat4.h"

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
			DualQuaternion(const Quaternion& rotation, const Vec3& translation);
			DualQuaternion(const DualQuaternion& dualQuat);

			DualQuaternion Normalized() const;
			DualQuaternion& Normalize();
			DualQuaternion Conjugate() const;
			Mat3 GetRotation() const;
			void SetRotation(const Mat3& matrix);
			Vec3 GetTranslation() const;
			void SetTranslation(const Vec3& vector);
			Quaternion GetRealQuaternion() const; 
			void SetRealQuaternion(const Quaternion& quaternion);
			Quaternion GetDualQuaternion() const;
			void SetDaulQuaternion(const Quaternion& quaternion);
			Mat4 GetTransformationMatrix() const;

			static float Dot(const DualQuaternion& leftDualQuat, const DualQuaternion& rightDualQuat);
			static DualQuaternion Sclerp(const DualQuaternion& leftDualQuat, const DualQuaternion& rightDualQuat, float t);
			static Vec3 TransformVector(const DualQuaternion& dualQuat, const Vec3& vector);

			DualQuaternion& operator=(const DualQuaternion& dualQuat);
			DualQuaternion& operator*=(const DualQuaternion& dualQuat);
			DualQuaternion& operator*=(float scalar);
			DualQuaternion& operator/=(float scalar);
			DualQuaternion& operator+=(const DualQuaternion& dualQuat);
			DualQuaternion& operator-=(const DualQuaternion& dualQuat);
		};

		DualQuaternion operator*(const DualQuaternion& leftDualQuat, const DualQuaternion& rightDualQuat);
		Vec3 operator*(const DualQuaternion& dualQuat, const Vec3& vector);
		DualQuaternion operator*(const DualQuaternion& leftDualQuat, float scalar);
		DualQuaternion operator/(const DualQuaternion& leftDualQuat, float scalar);
		DualQuaternion operator-(const DualQuaternion& leftDualQuat, const DualQuaternion& rightDualQuat);
		DualQuaternion operator+(const DualQuaternion& leftDualQuat, const DualQuaternion& rightDualQuat);

		std::ostream& operator<<(std::ostream& stream, const DualQuaternion& quaternion);
	}
}