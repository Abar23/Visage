#include <cmath>
#include <algorithm>
#include "DualQuaternion.h"
#include "MathFunctions.h"

namespace Visage
{
	namespace Math
	{

		DualQuaternion::DualQuaternion()
			: real(), dual()
		{
			dual.w = 0.0f;
		}
		
		DualQuaternion::DualQuaternion(const Quaternion& real, const Quaternion& dual)
			: real(real), dual(dual)
		{
		}

		DualQuaternion::DualQuaternion(const Quaternion& rotation, const Vec3& translation)
		{
			real = rotation;
			dual = (Quaternion(translation.x, translation.y, translation.z, 0.0f) * real) * 0.5f;
		}

		DualQuaternion::DualQuaternion(const DualQuaternion& dualQuat)
		{
			real = dualQuat.real;
			dual = dualQuat.dual;
		}

		DualQuaternion DualQuaternion::Normalized() const
		{
			float magnitude = Quaternion::Dot(real, real);
			if (!FloatIsEqual(magnitude, 0.0f))
			{
				float inverseMag = 1.0f / magnitude;
				return DualQuaternion(real * inverseMag,
									  dual * inverseMag);
			}
			else
			{
				return DualQuaternion(Quaternion(0.0f, 0.0f, 0.0f, 0.0f),
									  Quaternion(0.0f, 0.0f, 0.0f, 0.0f));
			}
		}

		DualQuaternion& DualQuaternion::Normalize()
		{
			float magnitude = Quaternion::Dot(real, real);
			if (!FloatIsEqual(magnitude, 0.0f))
			{
				float inverseMag = 1.0f / magnitude;
				return *this *= inverseMag;
			}
			else
			{
				return *this *= 0.0f;
			}
		}

		DualQuaternion DualQuaternion::Conjugate() const
		{
			return DualQuaternion(real.Conjugate(), dual.Conjugate());
		}

		Mat3 DualQuaternion::GetRotation() const
		{
			return real.GetRotationMatrix();
		}

		void DualQuaternion::SetRotation(const Mat3& matrix)
		{
			real.SetRotationMatrix(matrix);
		}

		Vec3 DualQuaternion::GetTranslation() const
		{
			Quaternion translation = dual * real.Conjugate() * 2.0f;
			
			return Vec3(translation.x,
						translation.y,
						translation.z);
		}

		void DualQuaternion::SetTranslation(const Vec3& vector)
		{
			dual = Quaternion(vector.x, vector.y, vector.x, 0.0f) * real * 0.5f;
		}

		Quaternion DualQuaternion::GetRealQuaternion() const
		{
			return real;
		}

		void DualQuaternion::SetRealQuaternion(const Quaternion& quaternion)
		{
			real = quaternion;
		}

		Quaternion DualQuaternion::GetDualQuaternion() const
		{
			return dual;
		}

		void DualQuaternion::SetDaulQuaternion(const Quaternion& quaternion)
		{
			dual = quaternion;
		}

		Mat4 DualQuaternion::GetTransformationMat4() const
		{
			Mat4 matrix;

			float x = real.x;
			float y = real.y;
			float z = real.z;
			float w = real.w;
			float xSquared = x * x;
			float ySquared = y * y;
			float zSquared = z * z;
			float wSquared = w * w;
			float xy = x * y;
			float xz = x * z;
			float yz = y * z;
			float wx = w * x;
			float wy = w * y;
			float wz = w * z;

			matrix(0, 0) = wSquared + xSquared - ySquared - zSquared;
			matrix(1, 0) = 2.0f * (xy + wz);
			matrix(2, 0) = 2.0f * (xz - wy);

			matrix(0, 1) = 2.0f * (xy - wz);
			matrix(1, 1) = wSquared + ySquared - xSquared - zSquared;
			matrix(2, 1) = 2.0f * (yz + wx);

			matrix(0, 2) = 2.0f * (xz + wy);
			matrix(1, 2) = 2.0f * (yz - wx);
			matrix(2, 2) = wSquared + zSquared - xSquared - ySquared;

			Vec3 translation = GetTranslation();

			matrix(0, 3) = translation.x;
			matrix(1, 3) = translation.y;
			matrix(2, 3) = translation.z;
			matrix(3, 3) = 1.0f;

			return matrix;
		}

		Mat3x4 DualQuaternion::GetTransformationMat3x4() const
		{
			Mat3x4 matrix;

			float x = real.x;
			float y = real.y;
			float z = real.z;
			float w = real.w;
			float xSquared = x * x;
			float ySquared = y * y;
			float zSquared = z * z;
			float wSquared = w * w;
			float xy = x * y;
			float xz = x * z;
			float yz = y * z;
			float wx = w * x;
			float wy = w * y;
			float wz = w * z;

			matrix(0, 0) = wSquared + xSquared - ySquared - zSquared;
			matrix(1, 0) = 2.0f * (xy + wz);
			matrix(2, 0) = 2.0f * (xz - wy);

			matrix(0, 1) = 2.0f * (xy - wz);
			matrix(1, 1) = wSquared + ySquared - xSquared - zSquared;
			matrix(2, 1) = 2.0f * (yz + wx);

			matrix(0, 2) = 2.0f * (xz + wy);
			matrix(1, 2) = 2.0f * (yz - wx);
			matrix(2, 2) = wSquared + zSquared - xSquared - ySquared;

			Vec3 translation = GetTranslation();

			matrix(0, 3) = translation.x;
			matrix(1, 3) = translation.y;
			matrix(2, 3) = translation.z;

			return matrix;
		}

		float DualQuaternion::Dot(const DualQuaternion& leftDualQuat, const DualQuaternion& rightDualQuat)
		{
			return Quaternion::Dot(leftDualQuat.real, rightDualQuat.real);
		}

		DualQuaternion DualQuaternion::Sclerp(const DualQuaternion& leftDualQuat, const DualQuaternion& rightDualQuat, float t)
		{
			float dot = Quaternion::Dot(leftDualQuat.real, rightDualQuat.real);
			
			DualQuaternion difference;
			if (dot < 0.0f)
			{
				difference = leftDualQuat.Conjugate() * (rightDualQuat * -1.0f);
			}
			else
			{
				difference = leftDualQuat.Conjugate() * rightDualQuat;
			}

			Vec3 realVector = Vec3(difference.real.x, difference.real.y, difference.real.z);
			Vec3 dualVector = Vec3(difference.dual.x, difference.dual.y, difference.dual.z);
			float inverseRealVectorMag = 1.0f / realVector.Magnitude();

			float angle = std::acosf(std::clamp(difference.real.w, -1.0f, 1.0f)) *2.0f;
			float pitch = difference.dual.w * inverseRealVectorMag * -2.0f;
			Vec3 direction = realVector * inverseRealVectorMag;
			Vec3 moment = (dualVector - direction * pitch * difference.real.w * 0.5f) * inverseRealVectorMag;

			angle *= t;
			pitch *= t;
			
			float halfAngle = 0.5f * angle;
			float sinHalfAngle = std::sinf(halfAngle);
			float cosHalfAngle = std::cosf(halfAngle);
			Quaternion real = Quaternion(direction * sinHalfAngle, cosHalfAngle);
			Quaternion dual = Quaternion(moment * sinHalfAngle + direction * pitch * 0.5f * cosHalfAngle,
										 -pitch * 0.5f * sinHalfAngle);

			return leftDualQuat * DualQuaternion(real, dual);

			return DualQuaternion();
		}

		Vec3 DualQuaternion::TransformVector(const DualQuaternion& dualQuat, const Vec3& vector)
		{
			DualQuaternion vectorDualQuat;
			vectorDualQuat.dual.x = vector.x;
			vectorDualQuat.dual.y = vector.y;
			vectorDualQuat.dual.z = vector.z;
			
			DualQuaternion result = dualQuat * vectorDualQuat;

			return result.GetTranslation();
		}

		DualQuaternion& DualQuaternion::operator=(const DualQuaternion& dualQuat)
		{
			real = dualQuat.real;
			dual = dualQuat.dual;
			return *this;
		}

		DualQuaternion& DualQuaternion::operator*=(const DualQuaternion& dualQuat)
		{
			real = real * dualQuat.real;
			dual = real * dualQuat.dual + dual * dualQuat.real;
			return *this;
		}

		DualQuaternion& DualQuaternion::operator*=(float scalar)
		{
			real *= scalar;
			dual *= scalar;
			return *this;
		}

		DualQuaternion& DualQuaternion::operator/=(float scalar)
		{
			real /= scalar;
			dual /= scalar;
			return *this;
		}

		DualQuaternion& DualQuaternion::operator+=(const DualQuaternion& dualQuat)
		{
			real += dualQuat.real;
			dual += dualQuat.dual;
			return *this;
		}

		DualQuaternion& DualQuaternion::operator-=(const DualQuaternion& dualQuat)
		{
			real -= dualQuat.real;
			dual -= dualQuat.dual;
			return *this;
		}
		
		DualQuaternion operator*(const DualQuaternion& leftDualQuat, const DualQuaternion& rightDualQuat)
		{
			DualQuaternion leftDualQuatCopy = leftDualQuat;
			return leftDualQuatCopy *= rightDualQuat;
		}

		Vec3 operator*(const DualQuaternion& dualQuat, const Vec3& vector)
		{
			return DualQuaternion::TransformVector(dualQuat, vector);
		}

		DualQuaternion operator*(const DualQuaternion& leftDualQuat, float scalar)
		{
			DualQuaternion leftDualQuatCopy = leftDualQuat;
			return leftDualQuatCopy *= scalar;
		}

		DualQuaternion operator/(const DualQuaternion& leftDualQuat, float scalar)
		{
			DualQuaternion leftDualQuatCopy = leftDualQuat;
			return leftDualQuatCopy /= scalar;
		}

		DualQuaternion operator-(const DualQuaternion& leftDualQuat, const DualQuaternion& rightDualQuat)
		{
			DualQuaternion leftDualQuatCopy = leftDualQuat;
			return leftDualQuatCopy -= rightDualQuat;
		}

		DualQuaternion operator+(const DualQuaternion& leftDualQuat, const DualQuaternion& rightDualQuat)
		{
			DualQuaternion leftDualQuatCopy = leftDualQuat;
			return leftDualQuatCopy += rightDualQuat;
		}

		std::ostream& operator<<(std::ostream& stream, const DualQuaternion& quaternion)
		{
			stream << "( " << quaternion.GetRealQuaternion() << ", " << quaternion.GetDualQuaternion() << " )";
			return stream;
		}
	}
}