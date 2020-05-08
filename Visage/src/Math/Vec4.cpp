#include <cmath>
#include "Vec4.h"
#include "MathFunctions.h"
#include "MathConstants.h"

namespace Visage
{
	namespace Math
	{
		Vec4::Vec4()
			: x(0.0f), y(0.0f), z(0.0f), w(0.0)
		{
		}

		Vec4::Vec4(const Vec4& vector)
			: x(vector.x), y(vector.y), z(vector.z), w(vector.w)
		{
		}

		Visage::Math::Vec4::Vec4(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w)
		{
		}

		Visage::Math::Vec4::Vec4(float x, float y, float z)
			: x(x), y(y), z(z), w(0.0f)
		{
		}

		Visage::Math::Vec4::Vec4(const float scalar)
			: x(scalar), y(scalar), z(scalar), w(scalar)
		{
		}

		float Vec4::Magnitude() const
		{
			return std::sqrt(x * x + y * y + z * z + w * w);
		}

		float Vec4::SqrMagnitude() const
		{
			return x * x + y * y + z * z + w * w;
		}

		Vec4 Vec4::Normalized() const
		{
			float magnitude = Magnitude();
			if (!FloatIsEqual(magnitude, 0.0f))
			{
				float inverseMag = 1.0f / magnitude;
				return Vec4(x * inverseMag,
							y * inverseMag,
							z * inverseMag,
							w * inverseMag);
			}
			else
			{
				return Zero();
			}
		}

		Vec4& Vec4::Normalize()
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

		Vec4 Vec4::Renormalized() const
		{
			float inverseMagnitude = FastInverseSqurRootAroundOne(SqrMagnitude());
			return Vec4(x * inverseMagnitude, y * inverseMagnitude, z * inverseMagnitude, w * inverseMagnitude);
		}

		Vec4& Vec4::Renormalize()
		{
			float inverseMagnitude = FastInverseSqurRootAroundOne(SqrMagnitude());
			return *this *= inverseMagnitude;
		}

		Vec4 Vec4::Negated() const
		{
			return *this * -1.0f;
		}

		Vec4& Vec4::Negate()
		{
			*this *= -1.0f;
			return *this;
		}

		Vec4 Vec4::Dot(const Vec4& leftVector, const Vec4& rightVector)
		{
			return leftVector.x * rightVector.x + 
				   leftVector.y * rightVector.y + 
				   leftVector.z * rightVector.z + 
				   leftVector.w * rightVector.w;
		}

		Vec4 Vec4::Zero()
		{
			return Vec4();
		}

		Vec4& Visage::Math::Vec4::operator=(const Vec4& vector)
		{
			x = vector.x;
			y = vector.y;
			z = vector.z;
			w = vector.w;
			return *this;
		}

		Vec4& Visage::Math::Vec4::operator+=(const Vec4& vector)
		{
			x += vector.x;
			y += vector.y;
			z += vector.z;
			w += vector.w;
			return *this;
		}

		Vec4& Visage::Math::Vec4::operator-=(const Vec4& vector)
		{
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;
			w -= vector.w;
			return *this;
		}

		Vec4& Visage::Math::Vec4::operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;
			return *this;
		}

		Vec4& Visage::Math::Vec4::operator/=(float scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			w /= scalar;
			return *this;
		}

		bool Visage::Math::operator==(const Vec4& leftVector, const Vec4& rightVector)
		{
			return FloatIsEqual(leftVector.x, rightVector.x) &&
				   FloatIsEqual(leftVector.y, rightVector.y) &&
				   FloatIsEqual(leftVector.z, rightVector.z) &&
				   FloatIsEqual(leftVector.w, rightVector.w);
		}

		bool Visage::Math::operator!=(const Vec4& leftVector, const Vec4& rightVector)
		{
			return !(leftVector == rightVector);
		}

		Vec4 Visage::Math::operator+(const Vec4& leftVector, const Vec4& rightVector)
		{
			Vec4 leftVectorCopy = leftVector;
			return leftVectorCopy += rightVector;
		}

		Vec4 Visage::Math::operator-(const Vec4& leftVector, const Vec4& rightVector)
		{
			Vec4 leftVectorCopy = leftVector;
			return leftVectorCopy -= rightVector;
		}

		Vec4 Visage::Math::operator*(const Vec4& vector, float scalar)
		{
			Vec4 vectorCopy = vector;
			return vectorCopy *= scalar;
		}

		Vec4 Visage::Math::operator/(const Vec4& vector, float scalar)
		{
			Vec4 vectorCopy = vector;
			return vectorCopy /= scalar;
		}

		std::ostream& Visage::Math::operator<<(std::ostream& stream, const Vec4& vector)
		{
			stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
		}
	}
}
