#include <cmath>
#include <algorithm>
#include <iostream>
#include "Quaternion.h"
#include "MathFunctions.h"
#include "MathConstants.h"

namespace Visage
{
	namespace Math
	{
		Quaternion::Quaternion()
			: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
		{
		}

		Quaternion::Quaternion(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w)
		{
		}

		Quaternion::Quaternion(const Vec3& unitVector, float angleInDegrees)
		{
			float halfAngle = DegreesToRad(angleInDegrees) / 2.0f;
			float cosHalfAngle = std::cos(halfAngle);
			float sinHalfAngle = std::sin(halfAngle);

			x = unitVector.x * sinHalfAngle;
			y = unitVector.y * sinHalfAngle;
			z = unitVector.z * sinHalfAngle;
			w = cosHalfAngle;
		}

		Quaternion::Quaternion(const Quaternion& quaternion)
			: x(quaternion.x), y(quaternion.y), z(quaternion.z), w(quaternion.w)
		{
		}

		float Quaternion::Norm() const
		{
			return std::sqrtf(SqrNorm());
		}

		float Quaternion::SqrNorm() const
		{
			return x * x + y * y + z * z + w * w;
		}

		Quaternion Quaternion::Normalized() const
		{
			float inverseNorm = 1.0f / std::sqrtf(SqrNorm());
			return Quaternion(x * inverseNorm, y * inverseNorm, z * inverseNorm, w * inverseNorm);
		}

		Quaternion& Quaternion::Normalize()
		{
			float inverseNorm = 1.0f / std::sqrtf(SqrNorm());
			*this *= inverseNorm;
			return *this;
		}

		Quaternion Quaternion::Renormalized() const
		{
			float inverseNorm = FastInverseSqurRootAroundOne(SqrNorm());
			return Quaternion(x * inverseNorm, y * inverseNorm, z * inverseNorm, w * inverseNorm);
		}

		Quaternion& Quaternion::Renormalize()
		{
			float inverseNorm = FastInverseSqurRootAroundOne(SqrNorm());
			*this *= inverseNorm;
			return *this;
		}

		Quaternion Quaternion::Inverted() const
		{
			return Quaternion(-x, -y, -x, w);
		}

		Quaternion& Quaternion::Invert()
		{
			x = -x;
			y = -x;
			z = -z;
			return *this;
		}

		Quaternion Quaternion::Conjugate() const
		{
			return Quaternion(-x, -y, -z, w);
		}

		Mat3 Quaternion::GetRotationMatrix() const
		{
			Mat3 matrix;

			float xSquared = x * x;
			float ySquared = y * y;
			float zSquared = z * z;
			float xy = x * y;
			float xz = x * z;
			float yz = y * z;
			float wx = w * x;
			float wy = w * y;
			float wz = w * z;

			matrix(0, 0) = 1.0f - 2.0f * (ySquared + zSquared);
			matrix(1, 0) = 2.0f * (xy + wz);
			matrix(2, 0) = 2.0f * (xz - wy);

			matrix(0, 1) = 2.0f * (xy - wz);
			matrix(1, 1) = 1.0f - 2.0f * (xSquared + zSquared);
			matrix(2, 1) = 2.0f * (yz + wx);

			matrix(0, 2) = 2.0f * (xz + wy);
			matrix(1, 2) = 2.0f * (yz - wx);
			matrix(2, 2) = 1.0f - 2.0f * (xSquared + ySquared);

			return matrix;
		}

		void Quaternion::SetRotationMatrix(const Mat3& matrix)
		{
			float m00 = matrix(0, 0);
			float m11 = matrix(1, 1);
			float m22 = matrix(2, 2);
			float diagonalSum = m00 + m11 + m22;

			if (diagonalSum > 0.0f)
			{
				w = std::sqrtf(diagonalSum + 1.0f) * 0.5f;
				float fraction = 0.25f / w;

				x = (matrix(2, 1) - matrix(1, 2)) * fraction;
				y = (matrix(0, 2) - matrix(2, 0)) * fraction;
				z = (matrix(1, 0) - matrix(0, 1)) * fraction;
			}
			else if (m00 > m11 && m00 > m22)
			{
				x = std::sqrtf(m00 - m11 - m22 + 1.0f) * 0.5f;
				float fraction = 0.25f / x;

				y = (matrix(1, 0) + matrix(0, 1)) * fraction;
				z = (matrix(0, 2) + matrix(2, 0)) * fraction;
				w = (matrix(2, 1) - matrix(1, 2)) * fraction;
			}
			else if (m11 > m22)
			{
				y = std::sqrtf(m11 - m00 - m22 + 1.0f) * 0.5f;
				float fraction = 0.25f / y;

				x = (matrix(1, 0) + matrix(0, 1)) * fraction;
				z = (matrix(2, 1) + matrix(1, 2)) * fraction;
				w = (matrix(0, 2) - matrix(2, 0)) * fraction;
			}
			else
			{
				z = std::sqrtf(m22 - m00 - m11 + 1.0f) * 0.5f;
				float fraction = 0.25f / z;

				x = (matrix(0, 2) + matrix(2, 0)) * fraction;
				y = (matrix(2, 1) + matrix(1, 2)) * fraction;
				w = (matrix(1, 0) - matrix(0, 1)) * fraction;
			}
		}

		Vec3 Quaternion::TransformVector(const Quaternion& quaterion, const Vec3& vector)
		{
			Vec3 vectorPart(quaterion.x, quaterion.y, quaterion.z);
			
			return (vector * (quaterion.w * quaterion.w - vectorPart.SqrMagnitude())) +
					vectorPart * (Vec3::Dot(vector, vectorPart) * 2.0f) +
					Vec3::Cross(vectorPart, vector) * (quaterion.w * 2.0f);
		}

		float Quaternion::Dot(const Quaternion& leftQuaterion, const Quaternion& rightQuaterion)
		{
			return leftQuaterion.x * rightQuaterion.x + 
				   leftQuaterion.y * rightQuaterion.y + 
				   leftQuaterion.z * rightQuaterion.z + 
				   leftQuaterion.w * rightQuaterion.w;
		}

		Quaternion Quaternion::MakeRotationX(float angleInDegrees)
		{
			float halfAngle = DegreesToRad(angleInDegrees) / 2.0f;
			return Quaternion(std::sin(halfAngle), 0.0f, 0.0f, std::cos(halfAngle));
		}

		Quaternion Quaternion::MakeRotationY(float angleInDegrees)
		{
			float halfAngle = DegreesToRad(angleInDegrees) / 2.0f;
			return Quaternion(0.0f, std::sin(halfAngle), 0.0f, std::cos(halfAngle));
		}

		Quaternion Quaternion::MakeRotationZ(float angleInDegrees)
		{
			float halfAngle = DegreesToRad(angleInDegrees) / 2.0f;
			return Quaternion(0.0f, 0.0f, std::sin(halfAngle), std::cos(halfAngle));
		}

		Quaternion Quaternion::MakeRotation(float angleInDegrees, const Vec3& unitVector)
		{
			return Quaternion(unitVector, angleInDegrees);
		}

		Quaternion Quaternion::Lerp(const Quaternion& leftQuaternion, const Quaternion& rightQuaternion, float t)
		{
			return leftQuaternion * (1.0f - t) + rightQuaternion * t;
		}

		Quaternion Quaternion::Nlerp(const Quaternion& leftQuaternion, const Quaternion& rightQuaternion, float t)
		{
			return Lerp(leftQuaternion, rightQuaternion, t).Normalized();
		}

		Quaternion Quaternion::Slerp(const Quaternion& leftQuaternion, const Quaternion& rightQuaternion, float t)
		{
			float dot = Quaternion::Dot(leftQuaternion, rightQuaternion);

			if (dot > dotThreshhold)
			{
				return Nlerp(leftQuaternion, rightQuaternion, t);
			}
			
			dot = std::clamp(dot, -1.0f, 1.0f);
			float theta = std::acos(dot) * t; // Angle between leftQuaternion and new quaternion at t
			Quaternion nlerpedQuaternion = Nlerp(leftQuaternion, rightQuaternion, dot);
			return leftQuaternion * std::cos(theta) + nlerpedQuaternion * std::sin(theta);
		}

		Quaternion& Quaternion::operator=(const Quaternion& quaternion)
		{
			x = quaternion.x;
			y = quaternion.y;
			z = quaternion.z;
			w = quaternion.w;
			return *this;
		}

		Quaternion& Quaternion::operator*=(const Quaternion& quaterion)
		{
			float x = this->x;
			float y = this->y;
			float z = this->z;
			float w = this->w;
			
			this->x = w * quaterion.x + x * quaterion.w + y * quaterion.z - z * quaterion.y;
			this->y = w * quaterion.y + y * quaterion.w + z * quaterion.x - x * quaterion.z;
			this->z = w * quaterion.z + z * quaterion.w + x * quaterion.y - y * quaterion.x;
			this->w = w * quaterion.w - x * quaterion.x - y * quaterion.y - z * quaterion.z;

			return *this;
		}

		Quaternion& Quaternion::operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;	
			return *this;
		}

		Quaternion& Quaternion::operator/=(float scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			w /= scalar;
			return *this;
		}

		Quaternion& Quaternion::operator+=(const Quaternion& quaternion)
		{
			x += quaternion.x;
			y += quaternion.y;
			z += quaternion.z;
			w += quaternion.w;
			return *this;
		}

		Quaternion& Quaternion::operator-=(const Quaternion& quaternion)
		{
			x -= quaternion.x;
			y -= quaternion.y;
			z -= quaternion.z;
			w -= quaternion.w;
			return *this;
		}


		Quaternion operator*(const Quaternion& leftQuaterion, const Quaternion& rightQuaterion)
		{
			Quaternion leftQuaterionCopy = leftQuaterion;
			return leftQuaterionCopy *= rightQuaterion;
		}

		Vec3 operator*(const Quaternion& quaternion, const Vec3& vector)
		{
			return Quaternion::TransformVector(quaternion, vector);
		}

		Quaternion operator*(const Quaternion& quaterion, float scalar)
		{
			Quaternion quaterionCopy = quaterion;
			return quaterionCopy *= scalar;
		}

		Quaternion operator/(const Quaternion& quaterion, float scalar)
		{
			Quaternion quaterionCopy = quaterion;
			return quaterionCopy /= scalar;
		}

		Quaternion operator+(const Quaternion& leftQuaterion, const Quaternion& rightQuaterion)
		{
			Quaternion leftQuaterionCopy = leftQuaterion;
			return leftQuaterionCopy += rightQuaterion;
		}

		Quaternion operator-(const Quaternion& leftQuaterion, const Quaternion& rightQuaterion)
		{
			Quaternion leftQuaterionCopy = leftQuaterion;
			return leftQuaterionCopy -= rightQuaterion;
		}
		std::ostream& operator<<(std::ostream& stream, const Quaternion& quaternion)
		{
			stream << "(" << quaternion.w << ", [" << quaternion.x << ", " << quaternion.y << ", " << quaternion.x << "])";
			return stream;
		}
	}
}