#pragma once

#include <ostream>
#include "Vector3D.h"

namespace Visage
{
	namespace Math
	{
		class Matrix3D
		{
		private:
			union
			{
				float entries[3][3];
				Vector3D columns[3];
			};

		public:
			Matrix3D();
			Matrix3D(float m00, float m01, float m02,
					 float m10, float m11, float m12,
					 float m20, float m21, float m22);
			Matrix3D(const Vector3D& firstRow, 
					 const Vector3D& secondRow, 
					 const Vector3D& thirdRow);
			Matrix3D(float diagonal);
			Matrix3D(const Matrix3D& matrix);

			~Matrix3D() = default;

			Matrix3D Inverse() const;
			Matrix3D Transpose() const;
			float Determinant() const;
			Vector3D GetColumn(int columnIndex) const;
			Vector3D GetRow(int rowIndex) const;

			static Matrix3D MakeRotationX(float angle);
			static Matrix3D MakeRotationY(float angle);
			static Matrix3D MakeRotationZ(float angle);
			static Matrix3D MakeRotaion(float angle, const Vector3D& axis);
			static Matrix3D MakeScale(float uniformScale);
			static Matrix3D MakeScale(float scaleX, float scaleY, float scaleZ);
			static Matrix3D MakeScale(const Vector3D& vector);
			static Matrix3D Identity();

			Matrix3D& operator=(const Matrix3D& matrix);
			
			const float& operator()(int rowIndex, int columnIndex) const;
			float& operator()(int rowIndex, int columnIndex);

			Matrix3D& operator*=(const Matrix3D& matrix);
			Vector3D operator*=(const Vector3D& vector);
			Matrix3D& operator*=(const float scalar);
		};

		Matrix3D operator*(const Matrix3D& leftMatrix, const Matrix3D& rightMatrix);
		Vector3D operator*(const Matrix3D& matrix, const Vector3D& vector);
		Matrix3D operator*(const Matrix3D& matrix, float scalar);

		std::ostream& operator<<(std::ostream& stream, const Matrix3D& matrix);
	}
}
