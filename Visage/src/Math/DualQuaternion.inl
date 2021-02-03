#pragma once

#include <assert.h>
#include <cmath>
#include <algorithm>
#include "MathFunctions.h"

namespace Visage
{
	namespace Math
	{
		template <typename T>
		DualQuaternion<T>::DualQuaternion()
			: real(), dual()
		{
			dual.w = 0;
		}
		
		template <typename T>
		DualQuaternion<T>::DualQuaternion(const Quaternion<T>& real, const Quaternion<T>& dual)
			: real(real), dual(dual)
		{
		}

		template <typename T>
		DualQuaternion<T>::DualQuaternion(const Quaternion<T>& rotation, const Vec3<T>& translation)
		{
			real = rotation;
			dual = (Quaternion<T>(translation.x, translation.y, translation.z, 0) * real) * static_cast<T>(0.5);
		}

		template <typename T>
		DualQuaternion<T>::DualQuaternion(const DualQuaternion<T>& dualQuat)
		{
			real = dualQuat.real;
			dual = dualQuat.dual;
		}

		template <typename T>
		DualQuaternion<T> DualQuaternion<T>::Normalized() const
		{
			assert(!NearEquals(Dot(), static_cast<T>(0)));

			T inverseMag = static_cast<T>(1) / Quaternion<T>::Dot(real, real);

			return DualQuaternion(real * inverseMag,
								  dual * inverseMag);
		}

		template <typename T>
		DualQuaternion<T>& DualQuaternion<T>::Normalize()
		{
			assert(!NearEquals(Dot(), static_cast<T>(0)));

			T inverseMag = static_cast<T>(1) / Quaternion<T>::Dot(real, real);

			return *this *= inverseMag;
		}

		template <typename T>
		DualQuaternion<T> DualQuaternion<T>::Conjugate() const
		{
			return DualQuaternion<T>(real.Conjugate(), dual.Conjugate());
		}

		template <typename T>
		Mat3<T> DualQuaternion<T>::GetRotation() const
		{
			return real.GetRotationMatrix();
		}

		template <typename T>
		void DualQuaternion<T>::SetRotation(const Mat3<T>& matrix)
		{
			real.SetRotationMatrix(matrix);
		}

		template <typename T>
		Vec3<T> DualQuaternion<T>::GetTranslation() const
		{
			Quaternion translation = dual * real.Conjugate() * static_cast<T>(2);
			
			return Vec3<T>(translation.x,
						   translation.y,
						   translation.z);
		}

		template <typename T>
		void DualQuaternion<T>::SetTranslation(const Vec3<T>& vector)
		{
			dual = Quaternion(vector.x, vector.y, vector.x, 0) * real * static_cast<T>(0.5);
		}

		template <typename T>
		Quaternion<T> DualQuaternion<T>::GetRealQuaternion() const
		{
			return real;
		}

		template <typename T>
		void DualQuaternion<T>::SetRealQuaternion(const Quaternion<T>& quaternion)
		{
			real = quaternion;
		}

		template <typename T>
		Quaternion<T> DualQuaternion<T>::GetDualQuaternion() const
		{
			return dual;
		}

		template <typename T>
		void DualQuaternion<T>::SetDaulQuaternion(const Quaternion<T>& quaternion)
		{
			dual = quaternion;
		}

		template <typename T>
		Mat4<T> DualQuaternion<T>::GetTransformationMat4() const
		{
			Mat4<T> matrix;

			T x = real.x;
			T y = real.y;
			T z = real.z;
			T w = real.w;
			T xSquared = x * x;
			T ySquared = y * y;
			T zSquared = z * z;
			T wSquared = w * w;
			T xy = x * y;
			T xz = x * z;
			T yz = y * z;
			T wx = w * x;
			T wy = w * y;
			T wz = w * z;

			matrix(0, 0) = wSquared + xSquared - ySquared - zSquared;
			matrix(1, 0) = static_cast<T>(2) * (xy + wz);
			matrix(2, 0) = static_cast<T>(2) * (xz - wy);

			matrix(0, 1) = static_cast<T>(2) * (xy - wz);
			matrix(1, 1) = wSquared + ySquared - xSquared - zSquared;
			matrix(2, 1) = static_cast<T>(2) * (yz + wx);

			matrix(0, 2) = static_cast<T>(2) * (xz + wy);
			matrix(1, 2) = static_cast<T>(2) * (yz - wx);
			matrix(2, 2) = wSquared + zSquared - xSquared - ySquared;

			Vec3<T> translation = GetTranslation();

			matrix(0, 3) = translation.x;
			matrix(1, 3) = translation.y;
			matrix(2, 3) = translation.z;
			matrix(3, 3) = 1;

			return matrix;
		}

		template <typename T>
		Mat3x4<T> DualQuaternion<T>::GetTransformationMat3x4() const
		{
			Mat3x4<T> matrix;

			T x = real.x;
			T y = real.y;
			T z = real.z;
			T w = real.w;
			T xSquared = x * x;
			T ySquared = y * y;
			T zSquared = z * z;
			T wSquared = w * w;
			T xy = x * y;
			T xz = x * z;
			T yz = y * z;
			T wx = w * x;
			T wy = w * y;
			T wz = w * z;

			matrix(0, 0) = wSquared + xSquared - ySquared - zSquared;
			matrix(1, 0) = static_cast<T>(2) * (xy + wz);
			matrix(2, 0) = static_cast<T>(2) * (xz - wy);

			matrix(0, 1) = static_cast<T>(2) * (xy - wz);
			matrix(1, 1) = wSquared + ySquared - xSquared - zSquared;
			matrix(2, 1) = static_cast<T>(2) * (yz + wx);

			matrix(0, 2) = static_cast<T>(2) * (xz + wy);
			matrix(1, 2) = static_cast<T>(2) * (yz - wx);
			matrix(2, 2) = wSquared + zSquared - xSquared - ySquared;

			Vec3<T> translation = GetTranslation();

			matrix(0, 3) = translation.x;
			matrix(1, 3) = translation.y;
			matrix(2, 3) = translation.z;

			return matrix;
		}

		template <typename T>
		T DualQuaternion<T>::Dot(const DualQuaternion<T>& leftDualQuat, const DualQuaternion<T>& rightDualQuat)
		{
			return Quaternion<T>::Dot(leftDualQuat.real, rightDualQuat.real);
		}

		template <typename T>
		DualQuaternion<T> DualQuaternion<T>::Sclerp(const DualQuaternion<T>& leftDualQuat, const DualQuaternion<T>& rightDualQuat, const T t)
		{
			T dot = Quaternion<T>::Dot(leftDualQuat.real, rightDualQuat.real);
			
			DualQuaternion<T> difference;
			if (dot < 0)
			{
				difference = leftDualQuat.Conjugate() * (rightDualQuat * static_cast<T>(-1));
			}
			else
			{
				difference = leftDualQuat.Conjugate() * rightDualQuat;
			}

			Vec3<T> realVector = Vec3<T>(difference.real.x, difference.real.y, difference.real.z);
			Vec3<T> dualVector = Vec3<T>(difference.dual.x, difference.dual.y, difference.dual.z);
			T inverseRealVectorMag = static_cast<T>(1) / realVector.Magnitude();

			T angle = std::acos(std::clamp(difference.real.w, static_cast<T>(-1), static_cast<T>(1))) * static_cast<T>(2);
			T pitch = difference.dual.w * inverseRealVectorMag * static_cast<T>(-2);
			Vec3<T> direction = realVector * inverseRealVectorMag;
			Vec3<T> moment = (dualVector - direction * pitch * difference.real.w * static_cast<T>(0.5)) * inverseRealVectorMag;

			angle *= t;
			pitch *= t;
			
			T halfAngle = static_cast<T>(0.5) * angle;
			T sinHalfAngle = std::sin(halfAngle);
			T cosHalfAngle = std::cos(halfAngle);
			Quaternion<T> real = Quaternion<T>(direction * sinHalfAngle, cosHalfAngle);
			Quaternion<T> dual = Quaternion<T>(moment * sinHalfAngle + direction * pitch * static_cast<T>(0.5) * cosHalfAngle,
										       -pitch * static_cast<T>(0.5) * sinHalfAngle);

			return leftDualQuat * DualQuaternion<T>(real, dual);
		}

		template <typename T>
		Vec3<T> DualQuaternion<T>::TransformVector(const DualQuaternion<T>& dualQuat, const Vec3<T>& vector)
		{
			DualQuaternion<T> vectorDualQuat;
			vectorDualQuat.dual.x = vector.x;
			vectorDualQuat.dual.y = vector.y;
			vectorDualQuat.dual.z = vector.z;
			
			DualQuaternion<T> result = dualQuat * vectorDualQuat;

			return result.GetTranslation();
		}

		template <typename T>
		DualQuaternion<T>& DualQuaternion<T>::operator=(const DualQuaternion<T>& dualQuat)
		{
			real = dualQuat.real;
			dual = dualQuat.dual;
			return *this;
		}

		template <typename T>
		DualQuaternion<T>& DualQuaternion<T>::operator*=(const DualQuaternion<T>& dualQuat)
		{
			real = real * dualQuat.real;
			dual = real * dualQuat.dual + dual * dualQuat.real;
			return *this;
		}

		template <typename T>
		DualQuaternion<T>& DualQuaternion<T>::operator*=(const T scalar)
		{
			real *= scalar;
			dual *= scalar;
			return *this;
		}

		template <typename T>
		DualQuaternion<T>& DualQuaternion<T>::operator/=(const T scalar)
		{
			real /= scalar;
			dual /= scalar;
			return *this;
		}

		template <typename T>
		DualQuaternion<T>& DualQuaternion<T>::operator+=(const DualQuaternion<T>& dualQuat)
		{
			real += dualQuat.real;
			dual += dualQuat.dual;
			return *this;
		}

		template <typename T>
		DualQuaternion<T>& DualQuaternion<T>::operator-=(const DualQuaternion<T>& dualQuat)
		{
			real -= dualQuat.real;
			dual -= dualQuat.dual;
			return *this;
		}
		
		template <typename T>
		DualQuaternion<T> operator*(const DualQuaternion<T>& leftDualQuat, const DualQuaternion<T>& rightDualQuat)
		{
			DualQuaternion<T> leftDualQuatCopy = leftDualQuat;
			return leftDualQuatCopy *= rightDualQuat;
		}

		template <typename T>
		DualQuaternion<T> operator*(const DualQuaternion<T>& dualQuat, const T scalar)
		{
			DualQuaternion<T> dualQuatCopy = dualQuat;
			return dualQuatCopy *= scalar;
		}

		template<typename T>
		DualQuaternion<T> operator*(const T scalar, const DualQuaternion<T>& dualQuat)
		{
			DualQuaternion<T> dualQuatCopy = dualQuat;
			return dualQuatCopy *= scalar;
		}

		template <typename T>
		DualQuaternion<T> operator/(const DualQuaternion<T>& dualQuat, const T scalar)
		{
			DualQuaternion<T> dualQuatCopy = dualQuat;
			return dualQuatCopy /= scalar;
		}

		template<typename T>
		DualQuaternion<T> operator/(const T scalar, const DualQuaternion<T>& dualQuat)
		{
			DualQuaternion<T> dualQuatCopy = dualQuat;
			return dualQuatCopy /= scalar;
		}

		template <typename T>
		DualQuaternion<T> operator-(const DualQuaternion<T>& leftDualQuat, const DualQuaternion<T>& rightDualQuat)
		{
			DualQuaternion<T> leftDualQuatCopy = leftDualQuat;
			return leftDualQuatCopy -= rightDualQuat;
		}

		template <typename T>
		DualQuaternion<T> operator+(const DualQuaternion<T>& leftDualQuat, const DualQuaternion<T>& rightDualQuat)
		{
			DualQuaternion<T> leftDualQuatCopy = leftDualQuat;
			return leftDualQuatCopy += rightDualQuat;
		}

		template <typename T>
		std::ostream& operator<<(std::ostream& stream, const DualQuaternion<T>& quaternion)
		{
			stream << "( " << quaternion.GetRealQuaternion() << ", " << quaternion.GetDualQuaternion() << " )";
			return stream;
		}
	}
}