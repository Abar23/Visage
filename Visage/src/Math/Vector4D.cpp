#include <cmath>

#include "Vector4D.h"
#include "MathFunctions.h"

namespace Visage
{
	namespace Math
	{
		Visage::Math::Vector4D::Vector4D()
			: x(0.0f), y(0.0f), z(0.0f), w(0.0)
		{
		}

		Visage::Math::Vector4D::Vector4D(const Vector4D& vector)
			: x(vector.x), y(vector.y), z(vector.z), w(vector.w)
		{
		}

		Visage::Math::Vector4D::Vector4D(const Vector3D& vector)
			: x(vector.x), y(vector.y), z(vector.z), w(0.0f)
		{
		}

		Visage::Math::Vector4D::Vector4D(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w)
		{
		}

		Visage::Math::Vector4D::Vector4D(float x, float y, float z)
			: x(x), y(y), z(z), w(0.0f)
		{
		}

		Visage::Math::Vector4D::Vector4D(const float scalar)
			: x(scalar), y(scalar), z(scalar), w(scalar)
		{
		}

		float Vector4D::Magnitude() const
		{
			return std::sqrt(x * x + y * y + z * z + w * w);
		}

		float Vector4D::SqrMagnitude() const
		{
			return x * x + y * y + z * z + w * w;
		}

		Vector4D Vector4D::Normalize() const
		{
			float magnitude = Magnitude();
			if (magnitude > 0.0f)
			{
				float oneOverMag = 1.0f / Magnitude();
				return Vector4D(x * oneOverMag,
								y * oneOverMag,
								z * oneOverMag,
								w * oneOverMag);
			}
			else
			{
				return Zero();
			}
		}

		Vector4D Vector4D::Negate() const
		{
			return *this * -1;
		}

		Vector4D Vector4D::Dot(const Vector4D& leftVector, const Vector4D& rightVector)
		{
			return leftVector.x * rightVector.x + 
				   leftVector.y * rightVector.y + 
				   leftVector.z * rightVector.z + 
				   leftVector.w * rightVector.w;
		}

		Vector3D Vector4D::Zero()
		{
			return Vector3D();
		}

		Vector4D& Visage::Math::Vector4D::operator=(const Vector4D& vector)
		{
			x = vector.x;
			y = vector.y;
			z = vector.z;
			w = vector.w;
			return *this;
		}

		Vector4D& Visage::Math::Vector4D::operator+=(const Vector4D& vector)
		{
			x += vector.x;
			y += vector.y;
			z += vector.z;
			w += vector.w;
			return *this;
		}

		Vector4D& Visage::Math::Vector4D::operator-=(const Vector4D& vector)
		{
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;
			w -= vector.w;
			return *this;
		}

		Vector4D& Visage::Math::Vector4D::operator*=(const float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;
			return *this;
		}

		Vector4D& Visage::Math::Vector4D::operator/=(const float scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			w /= scalar;
			return *this;
		}

		bool Visage::Math::operator==(const Vector4D& leftVector, const Vector4D& rightVector)
		{
			return FloatIsEqual(leftVector.x, rightVector.x) &&
				   FloatIsEqual(leftVector.y, rightVector.y) &&
				   FloatIsEqual(leftVector.z, rightVector.z) &&
				   FloatIsEqual(leftVector.w, rightVector.w);
		}

		bool Visage::Math::operator!=(const Vector4D& leftVector, const Vector4D& rightVector)
		{
			return !(leftVector == rightVector);
		}

		Vector4D Visage::Math::operator+(const Vector4D& leftVector, const Vector4D& rightVector)
		{
			return Vector4D(leftVector.x + rightVector.x,
							leftVector.y + rightVector.y,
							leftVector.z + rightVector.z,
							leftVector.w + rightVector.w);
		}

		Vector4D Visage::Math::operator-(const Vector4D& leftVector, const Vector4D& rightVector)
		{
			return Vector4D(leftVector.x - rightVector.x,
							leftVector.y - rightVector.y,
							leftVector.z - rightVector.z,
							leftVector.w - rightVector.w);
		}

		Vector4D Visage::Math::operator*(const Vector4D& vector, float scalar)
		{
			return Vector4D(vector.x * scalar,
							vector.y * scalar,
							vector.z * scalar,
							vector.w * scalar);
		}

		Vector4D Visage::Math::operator/(const Vector4D& vector, float scalar)
		{
			return Vector4D(vector.x / scalar,
							vector.y / scalar,
							vector.z / scalar,
							vector.w / scalar);
		}

		std::ostream& Visage::Math::operator<<(std::ostream& stream, const Vector4D& vector)
		{
			stream << "Vector4D: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
		}
	}
}
