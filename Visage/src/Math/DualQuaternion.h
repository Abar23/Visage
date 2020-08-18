#pragma once

#include "Quaternion.h"
#include "Vec3.h"
#include "Mat4.h"
#include "Mat3x4.h"

namespace Visage
{
	namespace Math
	{
		template <typename T>
		class DualQuaternion
		{
		private:
			Quaternion<T> real;
			Quaternion<T> dual;

		public:
			DualQuaternion();
			DualQuaternion(const Quaternion<T>& real, const Quaternion<T>& dual);
			DualQuaternion(const Quaternion<T>& rotation, const Vec3<T>& translation);
			DualQuaternion(const DualQuaternion<T>& dualQuat);

			DualQuaternion<T> Normalized() const;
			DualQuaternion<T>& Normalize();
			DualQuaternion<T> Conjugate() const;
			Mat3<T> GetRotation() const;
			void SetRotation(const Mat3<T>& matrix);
			Vec3<T> GetTranslation() const;
			void SetTranslation(const Vec3<T>& vector);
			Quaternion<T> GetRealQuaternion() const; 
			void SetRealQuaternion(const Quaternion<T>& quaternion);
			Quaternion<T> GetDualQuaternion() const;
			void SetDaulQuaternion(const Quaternion<T>& quaternion);
			Mat4<T> GetTransformationMat4() const;
			Mat3x4<T> GetTransformationMat3x4() const;

			static T Dot(const DualQuaternion<T>& leftDualQuat, const DualQuaternion<T>& rightDualQuat);
			static DualQuaternion<T> Sclerp(const DualQuaternion<T>& leftDualQuat, const DualQuaternion<T>& rightDualQuat, const T t);
			static Vec3<T> TransformVector(const DualQuaternion<T>& dualQuat, const Vec3<T>& vector);

			DualQuaternion<T>& operator=(const DualQuaternion<T>& dualQuat);
			DualQuaternion<T>& operator*=(const DualQuaternion<T>& dualQuat);
			DualQuaternion<T>& operator*=(const T scalar);
			DualQuaternion<T>& operator/=(const T scalar);
			DualQuaternion<T>& operator+=(const DualQuaternion<T>& dualQuat);
			DualQuaternion<T>& operator-=(const DualQuaternion<T>& dualQuat);

			friend Vec3<T> operator*(const DualQuaternion<T>& dualQuat, const Vec3<T>& vector)
			{
				return DualQuaternion<T>::TransformVector(dualQuat, vector);
			}
		};

		template <typename T>
		DualQuaternion<T> operator*(const DualQuaternion<T>& leftDualQuat, const DualQuaternion<T>& rightDualQuat);

		template <typename T>
		DualQuaternion<T> operator*(const DualQuaternion<T>& dualQuat, const T scalar);

		template <typename T>
		DualQuaternion<T> operator*(const T scalar, const DualQuaternion<T>& dualQuat);

		template <typename T>
		DualQuaternion<T> operator/(const DualQuaternion<T>& dualQuat, const T scalar);

		template <typename T>
		DualQuaternion<T> operator/(const T scalar, const DualQuaternion<T>& dualQuat);

		template <typename T>
		DualQuaternion<T> operator-(const DualQuaternion<T>& leftDualQuat, const DualQuaternion<T>& rightDualQuat);

		template <typename T>
		DualQuaternion<T> operator+(const DualQuaternion<T>& leftDualQuat, const DualQuaternion<T>& rightDualQuat);

		template <typename T>
		std::ostream& operator<<(std::ostream& stream, const DualQuaternion<T>& quaternion);
	}

	using dualquat = Math::DualQuaternion<float>;
	using dualquatd = Math::DualQuaternion<double>;
}

#include "DualQuaternion.inl"
