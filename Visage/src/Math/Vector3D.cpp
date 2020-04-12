#include <cmath>

#include "Vector3D.h"
#include "MathFunctions.h"

namespace Visage 
{
	namespace Math
	{
		Visage::Math::Vector3D::Vector3D()
			: x(0.0f), y(0.0f), z(0.0f)
		{
		}

		Visage::Math::Vector3D::Vector3D(float x, float y, float z)
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
			float oneOverMag = 1.0f / Magnitude();
			return Vector3D(x * oneOverMag, 
							y * oneOverMag, 
							z * oneOverMag);
		}

		Vector3D Visage::Math::Vector3D::Negate() const
		{
			return Vector3D(x * -1.0f, y * -1.0f, z * -1.0f);
		}

		float Visage::Math::Vector3D::Dot(const Vector3D& leftVector, const Vector3D& rightVector)
		{
			return leftVector.x * rightVector.x + leftVector.y * rightVector.y + leftVector.z * rightVector.z;
		}

		Vector3D Visage::Math::Vector3D::Cross(const Vector3D& leftVector, const Vector3D& rightVector)
		{
			return Vector3D(leftVector.y * rightVector.z - leftVector.z * rightVector.y,
							leftVector.z * rightVector.x - leftVector.x * rightVector.z,
							leftVector.x * rightVector.y - leftVector.y * rightVector.x);
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
			return Vector3D(0.0f, 1.0f, 0.0f);
		}

		Vector3D Vector3D::Forward()
		{
			return Vector3D(0.0f, -1.0f, 0.0f);
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

		Vector3D& Vector3D::operator*=(const float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		Vector3D& Vector3D::operator/=(const float scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			return *this;
		}

		bool operator==(const Vector3D& leftVector, const Vector3D& rightVector)
		{
			return FloatCompare(leftVector.x, rightVector.x) &&
					FloatCompare(leftVector.y, rightVector.y) &&
					FloatCompare(leftVector.z, rightVector.z);
		}

		bool operator!=(const Vector3D& leftVector, const Vector3D& rightVector)
		{
			return !(leftVector == rightVector);
		}

		Vector3D operator+(const Vector3D& leftVector, const Vector3D& rightVector)
		{
			return Vector3D(leftVector.x + rightVector.x, 
							leftVector.y + rightVector.y, 
							leftVector.z + rightVector.z);
		}

		Vector3D operator-(const Vector3D& leftVector, const Vector3D& rightVector)
		{
			return Vector3D(leftVector.x - rightVector.x, 
							leftVector.y - rightVector.y, 
							leftVector.z - rightVector.z);
		}

		Vector3D operator*(const Vector3D& vector, float scalar)
		{
			return Vector3D(vector.x * scalar, 
							vector.y * scalar, 
							vector.z * scalar);
		}

		Vector3D operator/(const Vector3D& vector, float scalar)
		{
			return Vector3D(vector.x / scalar, 
							vector.y / scalar, 
							vector.z / scalar);
		}
		std::ostream& operator<<(std::ostream& stream, const Vector3D& vector)
		{
			stream << "Vector3D: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
			return stream;
		}
	}
}