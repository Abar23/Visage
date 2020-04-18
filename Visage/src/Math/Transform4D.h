#pragma once

#include "Matrix4D.h"
#include "Vector3D.h"
#include "Vector3D.h"

namespace Visage
{
	namespace Math
	{
		class Transform4D
		{
		private:
			float entries[3][4];

		public:
			Transform4D();
			Transform4D(float m00, float m01, float m02, float m03,
						float m10, float m11, float m12, float m13,
						float m20, float m21, float m22, float m23);
			Transform4D(const Vector3D& firstColumn,
						const Vector3D& secondColumn,
						const Vector3D& thirdColumn,
						const Vector3D& fourthColumn);
			Transform4D(float diagonal);
			Transform4D(const Transform4D& transform);

			~Transform4D() = default;

			Transform4D Inverse() const;
			Transform4D Transpose() const;
			float Determinant() const;

		};
	}
}