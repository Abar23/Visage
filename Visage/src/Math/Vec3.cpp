#include <cmath>
#include "Vec3.h"
#include "MathFunctions.h"
#include "MathConstants.h"

namespace Visage 
{
	namespace Math
	{
		Vec3::Vec3()
			: x(0.0f), y(0.0f), z(0.0f)
		{
		}

		Vec3::Vec3(const Vec2& vector)
			: x(vector.x), y(vector.y), z(0.0f)
		{
		}

		Vec3::Vec3(float x, float y, float z)
			: x(x), y(y), z(z)
		{
		}

		Vec3::Vec3(float value)
			: x(value), y(value), z(value)
		{
		}

		float Visage::Math::Vec3::Magnitude() const
		{
			return std::sqrt(x * x + y * y + z * z);
		}

		float Visage::Math::Vec3::SqrMagnitude() const
		{
			return x * x + y * y + z * z;
		}

		Vec3 Visage::Math::Vec3::Normalize() const
		{
			float magnitude = Magnitude();
			if (!FloatIsEqual(magnitude, 0.0f))
			{
				float inverseMag = 1.0f / magnitude;
				return Vec3(x * inverseMag,
							y * inverseMag,
							z * inverseMag);
			}
			else
			{
				return Zero();
			}
		}

		Vec3& Vec3::Normalized()
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

		Vec3 Vec3::Renormalized() const
		{
			float inverseMagnitude = FastInverseSqurRootAroundOne(SqrMagnitude());
			return Vec3(x * inverseMagnitude, y * inverseMagnitude, z * inverseMagnitude);
		}

		Vec3& Vec3::Renormalize()
		{
			float inverseMagnitude = FastInverseSqurRootAroundOne(SqrMagnitude());
			return *this *= inverseMagnitude;
		}

		Vec3 Visage::Math::Vec3::Negated() const
		{
			return *this * -1.0f;
		}

		Vec3& Vec3::Negate()
		{
			*this *= -1.0f;
			return *this;
		}

		float Visage::Math::Vec3::Dot(const Vec3& leftVector, const Vec3& rightVector)
		{
			return leftVector.x * rightVector.x +
				   leftVector.y * rightVector.y +
				   leftVector.z * rightVector.z;
		}

		Vec3 Visage::Math::Vec3::Cross(const Vec3& leftVector, const Vec3& rightVector)
		{
			return Vec3(leftVector.y * rightVector.z - leftVector.z * rightVector.y,
						leftVector.z * rightVector.x - leftVector.x * rightVector.z,
						leftVector.x * rightVector.y - leftVector.y * rightVector.x);
		}

		Vec3 Vec3::Project(const Vec3& leftVector, const Vec3& rightVector)
		{
			return rightVector * (Dot(leftVector, rightVector) / Dot(rightVector, rightVector));
		}

		Vec3 Vec3::Reject(const Vec3& leftVector, const Vec3& rightVector)
		{
			return leftVector - Project(leftVector, rightVector);
		}

		Vec3 Vec3::Zero()
		{
			return Vec3(0.0f, 0.0f, 0.0f);
		}

		Vec3 Vec3::XAxis()
		{
			return Vec3(1.0f, 0.0f, 0.0f);
		}

		Vec3 Vec3::YAxis()
		{
			return Vec3(0.0f, 1.0f, 0.0f);
		}

		Vec3 Vec3::ZAxis()
		{
			return Vec3(0.0f, 0.0f, 1.0f);
		}

		Vec3 Vec3::Up()
		{
			return Vec3(0.0f, 1.0f, 0.0f);
		}

		Vec3 Vec3::Down()
		{
			return Vec3(0.0f, -1.0f, 0.0f);
		}

		Vec3 Vec3::Left()
		{
			return Vec3(-1.0f, 0.0f, 0.0f);
		}

		Vec3 Vec3::Right()
		{
			return Vec3(1.0f, 0.0f, 0.0f);
		}

		Vec3 Vec3::Back()
		{
			return Vec3(0.0f, 0.0f, 1.0f);
		}

		Vec3 Vec3::Forward()
		{
			return Vec3(0.0f, 0.0f, -1.0f);
		}

		Vec3& Vec3::operator=(const Vec3& vector)
		{
			x = vector.x;
			y = vector.y;
			z = vector.z;
			return *this;
		}

		Vec3& Vec3::operator+=(const Vec3& vector)
		{
			x += vector.x;
			y += vector.y;
			z += vector.z;
			return *this;
		}

		Vec3& Vec3::operator-=(const Vec3& vector)
		{
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;
			return *this;
		}

		Vec3& Vec3::operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		Vec3& Vec3::operator/=(float scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			return *this;
		}

		bool operator==(const Vec3& leftVector, const Vec3& rightVector)
		{
			return FloatIsEqual(leftVector.x, rightVector.x) &&
				   FloatIsEqual(leftVector.y, rightVector.y) &&
				   FloatIsEqual(leftVector.z, rightVector.z);
		}

		bool operator!=(const Vec3& leftVector, const Vec3& rightVector)
		{
			return !(leftVector == rightVector);
		}

		Vec3 operator+(const Vec3& leftVector, const Vec3& rightVector)
		{
			Vec3 leftVectorCopy = leftVector;
			return leftVectorCopy += rightVector;
		}

		Vec3 operator-(const Vec3& leftVector, const Vec3& rightVector)
		{
			Vec3 leftVectorCopy = leftVector;
			return leftVectorCopy -= rightVector;
		}

		Vec3 operator*(const Vec3& vector, float scalar)
		{
			Vec3 vectorCopy = vector;
			return vectorCopy *= scalar;
		}

		Vec3 operator/(const Vec3& vector, float scalar)
		{
			Vec3 vectorCopy = vector;
			return vectorCopy /= scalar;
		}
		std::ostream& operator<<(std::ostream& stream, const Vec3& vector)
		{
			stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
			return stream;
		}
	}
}
