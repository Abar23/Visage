#include <cstring>
#include "Matrix4D.h"

namespace Visage
{
	namespace Math
	{
		Visage::Math::Matrix4D::Matrix4D()
			: entries{0.0f} 
		{
		}

		Matrix4D::Matrix4D(float m00, float m01, float m02, float m03, 
						   float m10, float m11, float m12, float m13, 
						   float m20, float m21, float m22, float m23, 
						   float m30, float m31, float m32, float m33)
		{
			entries[0][0] = m00;
			entries[0][1] = m10;
			entries[0][2] = m20;
			entries[0][3] = m30;

			entries[1][0] = m01;
			entries[1][1] = m11;
			entries[1][2] = m21;
			entries[1][3] = m31;

			entries[2][0] = m02;
			entries[2][1] = m12;
			entries[2][2] = m22;
			entries[2][3] = m32;

			entries[3][0] = m03;
			entries[3][1] = m13;
			entries[3][2] = m23;
			entries[3][3] = m33;
		}

		Matrix4D::Matrix4D(const Vector4D& firstRow, const Vector4D& secondRow, const Vector4D& thirdRow, const Vector4D& fourthRow)
		{
			entries[0][0] = firstRow.x;
			entries[0][1] = firstRow.y;
			entries[0][2] = firstRow.z;
			entries[0][3] = firstRow.w;

			entries[1][0] = secondRow.x;
			entries[1][1] = secondRow.y;
			entries[1][2] = secondRow.z;
			entries[1][3] = secondRow.w;

			entries[2][0] = thirdRow.x;
			entries[2][1] = thirdRow.y;
			entries[2][2] = thirdRow.z;
			entries[2][3] = thirdRow.w;

			entries[3][0] = fourthRow.x;
			entries[3][1] = fourthRow.y;
			entries[3][2] = fourthRow.z;
			entries[3][3] = fourthRow.w;
		}

		Matrix4D::Matrix4D(const float diagonal)
			: entries{ 0.0f }
		{
			entries[0][0] = diagonal;
			entries[1][1] = diagonal;
			entries[2][2] = diagonal;
			entries[3][3] = diagonal;
		}

		Matrix4D::Matrix4D(const Matrix4D& matrix)
		{
			memccpy(entries, matrix.entries, 16 * sizeof(float));
		}

		Matrix4D Matrix4D::Inverse() const
		{
			Vector3D a = reinterpret_cast<const Vector3D&>(columns[0]);
			Vector3D b = reinterpret_cast<const Vector3D&>(columns[1]);
			Vector3D c = reinterpret_cast<const Vector3D&>(columns[2]);
			Vector3D d = reinterpret_cast<const Vector3D&>(columns[3]);

			float x = entries[0][3];
			float y = entries[1][3];
			float z = entries[2][3];
			float w = entries[3][3];

			Vector3D s = Vector3D::Cross(a, b);
			Vector3D t = Vector3D::Cross(c, d);
			Vector3D u = a * y - b * x;
			Vector3D v = c * w - d * z;

			float inverseDet = 1.0f / Vector3D::Dot(s, v) - Vector3D::Dot(t, u);
			s *= inverseDet;
			t *= inverseDet;
			u *= inverseDet;
			v *= inverseDet;

			Vector3D firstRow = Vector3D::Cross(b, v) + t * y;
			Vector3D secondRow = Vector3D::Cross(v, a) - t * x;
			Vector3D thirdRow = Vector3D::Cross(d, u) + s * w;
			Vector3D fourthRow = Vector3D::Cross(u, c) - s * z;

			return Matrix4D(firstRow.x, firstRow.y, firstRow.z, -Vector3D::Dot(b, t),
							secondRow.x, secondRow.y, secondRow.z, Vector3D::Dot(a, t),
							thirdRow.x, thirdRow.y, thirdRow.z, -Vector3D::Dot(d, s),
							fourthRow.x, fourthRow.y, fourthRow.z, Vector3D::Dot(c, s));
		}

		float Matrix4D::Determinant() const
		{
			Vector3D a = reinterpret_cast<const Vector3D&>(columns[0]);
			Vector3D b = reinterpret_cast<const Vector3D&>(columns[1]);
			Vector3D c = reinterpret_cast<const Vector3D&>(columns[2]);
			Vector3D d = reinterpret_cast<const Vector3D&>(columns[3]);

			Vector3D s = Vector3D::Cross(a, b);
			Vector3D t = Vector3D::Cross(c, d);
			Vector3D u = a * entries[1][3] - b * entries[0][3];
			Vector3D v = c * entries[3][3] - d * entries[2][3];

			return Vector3D::Dot(s, v) - Vector3D::Dot(t, u);
		}


	}
}
