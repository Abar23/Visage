#include <cmath>
#include "Vector3D.h"
#include "MathFunctions.h"
#include "MathConstants.h"

namespace Visage 
{
	namespace Math
	{
		Vector3D::Vector3D()
			: x(0.0f), y(0.0f), z(0.0f)
		{
		}

		Vector3D::Vector3D(const Vector2D& vector)
			: x(vector.x), y(vector.y), z(0.0f)
		{
		}

		Vector3D::Vector3D(float x, float y, float z)
			: x(x), y(y), z(z)
		{
		}

		Vector3D::Vector3D(float value)
			: x(value), y(value), z(value)
		{
		}

		float Visage::Math::Vector3D::Magnitude() const
		{
			return std::sqrt(x * x + y * y + z * z);
		}

		float Visage::Math::Vector3D::SqrMagnitude() const
		{
			return x * x + y * y + z * z;
		}

		Vector3D Visage::Math::Vector3D::Normalize() const
		{
			float magnitude = Magnitude();
			if (!FloatIsEqual(magnitude, 0.0f))
			{
				float inverseMag = 1.0f / magnitude;
				return Vector3D(x * inverseMag,
								y * inverseMag,
								z * inverseMag);
			}
			else
			{
				return Zero();
			}
		}

		Vector3D& Vector3D::Normalized()
		{
			float magnitude = Magnitude();
			if (!FloatIsEqual(magnitude, 0.0f))
			{
				float inverseMag = 1.0f / magnitude;
				*this *= inverseMag;
			}
			else
			{
				*this *= 0.0f;
			}

			return *this;
		}

		Vector3D Visage::Math::Vector3D::Negated() const
		{
			return *this * -1.0f;
		}

		Vector3D& Vector3D::Negate()
		{
			*this *= -1.0f;
			return *this;
		}

		float Visage::Math::Vector3D::Dot(const Vector3D& leftVector, const Vector3D& rightVector)
		{
			return leftVector.x * rightVector.x +
				   leftVector.y * rightVector.y +
				   leftVector.z * rightVector.z;
		}

		Vector3D Visage::Math::Vector3D::Cross(const Vector3D& leftVector, const Vector3D& rightVector)
		{
			return Vector3D(leftVector.y * rightVector.z - leftVector.z * rightVector.y,
							leftVector.z * rightVector.x - leftVector.x * rightVector.z,
							leftVector.x * rightVector.y - leftVector.y * rightVector.x);
		}

		Vector3D Vector3D::Project(const Vector3D& leftVector, const Vector3D& rightVector)
		{
			return rightVector * (Dot(leftVector, rightVector) / Dot(rightVector, rightVector));
		}

		Vector3D Vector3D::Reject(const Vector3D& leftVector, const Vector3D& rightVector)
		{
			return leftVector - Project(leftVector, rightVector);
		}

		Vector3D Vector3D::Zero()
		{
			return Vector3D(0.0f, 0.0f, 0.0f);
		}

		Vector3D Vector3D::XAxis()
		{
			return Vector3D(1.0f, 0.0f, 0.0f);
		}

		Vector3D Vector3D::YAxis()
		{
			return Vector3D(0.0f, 1.0f, 0.0f);
		}

		Vector3D Vector3D::ZAxis()
		{
			return Vector3D(0.0f, 0.0f, 1.0f);
		}

		Vector3D Vector3D::Up()
		{
			return Vector3D(0.0f, 1.0f, 0.0f);
		}

		Vector3D Vector3D::Down()
		{
			return Vector3D(0.0f, -1.0f, 0.0f);
		}

		Vector3D Vector3D::Left()
		{
			return Vector3D(-1.0f, 0.0f, 0.0f);
		}

		Vector3D Vector3D::Right()
		{
			return Vector3D(1.0f, 0.0f, 0.0f);
		}

		Vector3D Vector3D::Back()
		{
			return Vector3D(0.0f, 0.0f, 1.0f);
		}

		Vector3D Vector3D::Forward()
		{
			return Vector3D(0.0f, 0.0f, -1.0f);
		}

		Vector3D& Vector3D::operator=(const Vector3D& vector)
		{
			x = vector.x;
			y = vector.y;
			z = vector.z;
			return *this;
		}

		Vector3D& Vector3D::operator+=(const Vector3D& vector)
		{
			x += vector.x;
			y += vector.y;
			z += vector.z;
			return *this;
		}

		Vector3D& Vector3D::operator-=(const Vector3D& vector)
		{
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;
			return *this;
		}

		Vector3D& Vector3D::operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		Vector3D& Vector3D::operator/=(float scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			return *this;
		}

		bool operator==(const Vector3D& leftVector, const Vector3D& rightVector)
		{
			return FloatIsEqual(leftVector.x, rightVector.x) &&
				   FloatIsEqual(leftVector.y, rightVector.y) &&
				   FloatIsEqual(leftVector.z, rightVector.z);
		}

		bool operator!=(const Vector3D& leftVector, const Vector3D& rightVector)
		{
			return !(leftVector == rightVector);
		}

		Vector3D operator+(const Vector3D& leftVector, const Vector3D& rightVector)
		{
			Vector3D leftVectorCopy = leftVector;
			return leftVectorCopy += rightVector;
		}

		Vector3D operator-(const Vector3D& leftVector, const Vector3D& rightVector)
		{
			Vector3D leftVectorCopy = leftVector;
			return leftVectorCopy -= rightVector;
		}

		Vector3D operator*(const Vector3D& vector, float scalar)
		{
			Vector3D vectorCopy = vector;
			return vectorCopy *= scalar;
		}

		Vector3D operator/(const Vector3D& vector, float scalar)
		{
			Vector3D vectorCopy = vector;
			return vectorCopy /= scalar;
		}
		std::ostream& operator<<(std::ostream& stream, const Vector3D& vector)
		{
			stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
			return stream;
		}
	}
}
