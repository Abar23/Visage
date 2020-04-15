#include <cmath>
#include "Vector2D.h"
#include "MathFunctions.h"

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

		Vector2D Vector2D::Normalize() const
		{
			float magnitude = Magnitude();
			if (magnitude > 0.0f)
			{
				float inverseMag = 1.0f / Magnitude();
				return Vector2D(x * inverseMag, y * inverseMag);
			}
			else
			{
				return Zero();
			}
		}

		Vector2D Vector2D::Negate() const
		{
			return *this * -1;
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

		Vector2D& Vector2D::operator*=(const float scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		Vector2D& Vector2D::operator/=(const float scalar)
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
			return Vector2D(leftVector.x + rightVector.x, 
							leftVector.y + rightVector.y);
		}

		Vector2D operator-(const Vector2D& leftVector, const Vector2D& rightVector)
		{
			return Vector2D(leftVector.x - rightVector.x,
							leftVector.y - rightVector.y);
		}

		Vector2D operator*(const Vector2D& vector, float scalar)
		{
			return Vector2D(vector.x * scalar,
							vector.y * scalar);
		}

		Vector2D operator/(const Vector2D& vector, float scalar)
		{
			return Vector2D(vector.x / scalar,
							vector.y / scalar);
		}

		std::ostream& operator<<(std::ostream& stream, const Vector2D& vector)
		{
			stream << "(" << vector.x << ", " << vector.y << ")";
			return stream;
		}
	}
}
