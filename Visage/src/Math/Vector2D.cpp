#include <cmath>
#include "Vector2D.h"
#include "MathFunctions.h"
#include "MathConstants.h"

namespace Visage
{
	namespace Math
	{
		Vector2D::Vector2D()
			: x(0.0f), y(0.0f)
		{
		}

		Vector2D::Vector2D(float x, float y)
			: x(x), y(y)
		{
		}

		Vector2D::Vector2D(float scalar)
			: x(scalar), y(scalar)
		{
		}

		Vector2D::Vector2D(const Vector2D& vector)
			: x(vector.x), y(vector.y)
		{
		}

		Vector2D Visage::Math::Vector2D::Zero()
		{
			return Vector2D();
		}

		Vector2D Vector2D::XAxis()
		{
			return Vector2D(1.0f, 0.0f);
		}

		Vector2D Vector2D::YAxis()
		{
			return Vector2D(0.0f, 1.0f);
		}

		Vector2D Vector2D::Up()
		{
			return Vector2D(1.0f, 0.0f);
		}

		Vector2D Vector2D::Down()
		{
			return Vector2D(-1.0f, 0.0f);
		}

		Vector2D Vector2D::Left()
		{
			return Vector2D(0.0f, -1.0f);
		}

		Vector2D Vector2D::Right()
		{
			return Vector2D(0.0f, 1.0f);
		}

		float Vector2D::Magnitude() const
		{
			return std::sqrt(x * x + y * y);
		}
		float Vector2D::SqrMagnitude() const
		{
			return x * x + y * y;
		}

		Vector2D Vector2D::Normalized() const
		{
			float magnitude = Magnitude();
			if (!FloatIsEqual(magnitude, 0.0f))
			{
				float inverseMag = 1.0f / magnitude;
				return Vector2D(x * inverseMag, y * inverseMag);
			}
			else
			{
				return Zero();
			}
		}

		Vector2D& Vector2D::Normalized()
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

		Vector2D Vector2D::Renormalized() const
		{
			float inverseMagnitude = FastInverseSqurRootAroundOne(SqrMagnitude());
			return Vector2D(x * inverseMagnitude, y * inverseMagnitude);
		}

		Vector2D& Vector2D::Renormalize()
		{
			float inverseMagnitude = FastInverseSqurRootAroundOne(SqrMagnitude());
			return *this *= inverseMagnitude;
		}

		Vector2D Vector2D::Negated() const
		{
			return *this * -1.0f;
		}

		Vector2D& Vector2D::Negate()
		{
			*this *= -1.0f;
			return *this;
		}

		float Vector2D::Dot(const Vector2D& leftVector, const Vector2D& rightVector)
		{
			return leftVector.x * rightVector.x + leftVector.y + rightVector.y;
		}

		Vector2D Vector2D::Project(const Vector2D& leftVector, const Vector2D& rightVector)
		{
			return rightVector * (Dot(leftVector, rightVector) / Dot(leftVector, rightVector));
		}

		Vector2D Vector2D::Reject(const Vector2D& leftVector, const Vector2D& rightVector)
		{
			return leftVector - Project(leftVector, rightVector);
		}

		Vector2D& Vector2D::operator=(const Vector2D& vector)
		{
			x = vector.x;
			y = vector.y;
			return *this;
		}

		Vector2D& Vector2D::operator+=(const Vector2D& vector)
		{
			x += vector.x;
			y += vector.y;
			return *this;
		}

		Vector2D& Vector2D::operator-=(const Vector2D& vector)
		{
			x -= vector.x;
			y -= vector.y;
			return *this;
		}

		Vector2D& Vector2D::operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		Vector2D& Vector2D::operator/=(float scalar)
		{
			x /= scalar;
			y /= scalar;
			return *this;
		}

		bool operator==(const Vector2D& leftVector, const Vector2D& rightVector)
		{
			return FloatIsEqual(leftVector.x, rightVector.x) &&
				   FloatIsEqual(leftVector.y, rightVector.y);
		}

		bool operator!=(const Vector2D& leftVector, const Vector2D& rightVector)
		{
			return !(leftVector == rightVector);
		}

		Vector2D operator+(const Vector2D& leftVector, const Vector2D& rightVector)
		{
			Vector2D leftVectorCopy = leftVector;
			return leftVectorCopy += rightVector;
		}

		Vector2D operator-(const Vector2D& leftVector, const Vector2D& rightVector)
		{
			Vector2D leftVectorCopy = leftVector;
			return leftVectorCopy -= rightVector;
		}

		Vector2D operator*(const Vector2D& vector, float scalar)
		{
			Vector2D vectorCopy = vector;
			return vectorCopy *= scalar;
		}

		Vector2D operator/(const Vector2D& vector, float scalar)
		{
			Vector2D vectorCopy = vector;
			return vectorCopy /= scalar;
		}

		std::ostream& operator<<(std::ostream& stream, const Vector2D& vector)
		{
			stream << "(" << vector.x << ", " << vector.y << ")";
			return stream;
		}
	}
}
