#include <cstring>
#include "Transform4D.h"

namespace Visage
{
	namespace Math
	{
		Transform4D::Transform4D()
			: entries{ 0.0f }
		{
		}

		Transform4D::Transform4D(float m00, float m01, float m02, float m03,
								 float m10, float m11, float m12, float m13,
								 float m20, float m21, float m22, float m23)
		{
			entries[0][0] = m00;
			entries[0][1] = m10;
			entries[0][2] = m20;

			entries[1][0] = m01;
			entries[1][1] = m11;
			entries[1][2] = m21;

			entries[2][0] = m02;
			entries[2][1] = m12;
			entries[2][2] = m22;

			entries[3][0] = m03;
			entries[3][1] = m13;
			entries[3][2] = m23;

			entries[0][3] = entries[1][3] = entries[2][3] = 0.0f;
			entries[3][3] = 1.0f;
		}

		Transform4D::Transform4D(const Vector3D& firstRow, 
								 const Vector3D& secondRow, 
								 const Vector3D& thirdRow, 
								 const Vector3D& fourthRow)
		{
			entries[0][0] = firstRow.x;
			entries[0][1] = firstRow.y;
			entries[0][2] = firstRow.z;

			entries[1][0] = secondRow.x;
			entries[1][1] = secondRow.y;
			entries[1][2] = secondRow.z;

			entries[2][0] = thirdRow.x;
			entries[2][1] = thirdRow.y;
			entries[2][2] = thirdRow.z;

			entries[3][0] = fourthRow.x;
			entries[3][1] = fourthRow.y;
			entries[3][2] = fourthRow.z;

			entries[0][3] = entries[1][3] = entries[2][3] = 0.0f;
			entries[3][3] = 1.0f;
		}

		Transform4D::Transform4D(float diagonal)
			: entries{ 0.0f }
		{
			entries[0][0] = diagonal;
			entries[1][1] = diagonal;
			entries[2][2] = diagonal;
			entries[3][3] = diagonal;
		}

		Transform4D::Transform4D(const Transform4D& transform)
		{
			std::memcpy(entries, transform.entries, sizeof(Transform4D));
		}

		Transform4D Transform4D::Inverse() const
		{
			return Transform4D();
		}
		Transform4D Transform4D::Transpose() const
		{
			return Transform4D();
		}
		float Transform4D::Determinant() const
		{
			return 0.0f;
		}
	}
}
