#include <cmath>
#include "Vec2.h"
#include "MathFunctions.h"
#include "MathConstants.h"

namespace Visage
{
	namespace Math
	{
		Vec2::Vec2()
			: x(0.0f), y(0.0f)
		{
		}

		Vec2::Vec2(float x, float y)
			: x(x), y(y)
		{
		}

		Vec2::Vec2(float scalar)
			: x(scalar), y(scalar)
		{
		}

		Vec2::Vec2(const Vec2& vector)
			: x(vector.x), y(vector.y)
		{
		}

		Vec2 Visage::Math::Vec2::Zero()
		{
			return Vec2();
		}

		Vec2 Vec2::XAxis()
		{
			return Vec2(1.0f, 0.0f);
		}

		Vec2 Vec2::YAxis()
		{
			return Vec2(0.0f, 1.0f);
		}

		Vec2 Vec2::Up()
		{
			return Vec2(0.0f, 1.0f);
		}

		Vec2 Vec2::Down()
		{
			return Vec2(0.0f, -1.0f);
		}

		Vec2 Vec2::Left()
		{
			return Vec2(-1.0f, 0.0f);
		}

		Vec2 Vec2::Right()
		{
			return Vec2(1.0f, 0.0f);
		}

		float Vec2::Magnitude() const
		{
			return std::sqrt(x * x + y * y);
		}

		float Vec2::SqrMagnitude() const
		{
			return x * x + y * y;
		}

		Vec2 Vec2::Normalized() const
		{
			float magnitude = Magnitude();
			if (!FloatIsEqual(magnitude, 0.0f))
			{
				float inverseMag = 1.0f / magnitude;
				return Vec2(x * inverseMag, y * inverseMag);
			}
			else
			{
				return Zero();
			}
		}

		Vec2& Vec2::Normalize()
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

		Vec2 Vec2::Renormalized() const
		{
			float inverseMagnitude = FastInverseSqurRootAroundOne(SqrMagnitude());
			return Vec2(x * inverseMagnitude, y * inverseMagnitude);
		}

		Vec2& Vec2::Renormalize()
		{
			float inverseMagnitude = FastInverseSqurRootAroundOne(SqrMagnitude());
			return *this *= inverseMagnitude;
		}

		Vec2 Vec2::Negated() const
		{
			return *this * -1.0f;
		}

		Vec2& Vec2::Negate()
		{
			*this *= -1.0f;
			return *this;
		}

		float Vec2::Dot(const Vec2& leftVector, const Vec2& rightVector)
		{
			return leftVector.x * rightVector.x + leftVector.y * rightVector.y;
		}

		Vec2 Vec2::Project(const Vec2& leftVector, const Vec2& rightVector)
		{
			return rightVector * (Dot(leftVector, rightVector) / Dot(leftVector, rightVector));
		}

		Vec2 Vec2::Reject(const Vec2& leftVector, const Vec2& rightVector)
		{
			return leftVector - Project(leftVector, rightVector);
		}

		Vec2 Vec2::Lerp(const Vec2& leftVector, const Vec2& rightVector, float t)
		{
			return leftVector * (1.0f - t) + rightVector * t;
		}

		Vec2& Vec2::operator=(const Vec2& vector)
		{
			x = vector.x;
			y = vector.y;
			return *this;
		}

		Vec2& Vec2::operator+=(const Vec2& vector)
		{
			x += vector.x;
			y += vector.y;
			return *this;
		}

		Vec2& Vec2::operator-=(const Vec2& vector)
		{
			x -= vector.x;
			y -= vector.y;
			return *this;
		}

		Vec2& Vec2::operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		Vec2& Vec2::operator/=(float scalar)
		{
			x /= scalar;
			y /= scalar;
			return *this;
		}

		bool operator==(const Vec2& leftVector, const Vec2& rightVector)
		{
			return FloatIsEqual(leftVector.x, rightVector.x) &&
				   FloatIsEqual(leftVector.y, rightVector.y);
		}

		bool operator!=(const Vec2& leftVector, const Vec2& rightVector)
		{
			return !(leftVector == rightVector);
		}

		Vec2 operator+(const Vec2& leftVector, const Vec2& rightVector)
		{
			Vec2 leftVectorCopy = leftVector;
			return leftVectorCopy += rightVector;
		}

		Vec2 operator-(const Vec2& leftVector, const Vec2& rightVector)
		{
			Vec2 leftVectorCopy = leftVector;
			return leftVectorCopy -= rightVector;
		}

		Vec2 operator*(const Vec2& vector, float scalar)
		{
			Vec2 vectorCopy = vector;
			return vectorCopy *= scalar;
		}

		Vec2 operator/(const Vec2& vector, float scalar)
		{
			Vec2 vectorCopy = vector;
			return vectorCopy /= scalar;
		}

		std::ostream& operator<<(std::ostream& stream, const Vec2& vector)
		{
			stream << "(" << vector.x << ", " << vector.y << ")";
			return stream;
		}
	}
}
