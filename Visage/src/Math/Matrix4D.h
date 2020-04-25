#pragma once

#include "Vector4D.h"
#include "Matrix3D.h"

namespace Visage
{
	namespace Math
	{
		class Matrix4D
		{
		protected:
			float entries[4][4];

		public:
			Matrix4D();
			Matrix4D(float m00, float m01, float m02, float m03,
					 float m10, float m11, float m12, float m13,
					 float m20, float m21, float m22, float m23,
					 float m30, float m31, float m32, float m33);
			Matrix4D(const Vector4D& firstRow,
					 const Vector4D& secondRow,
					 const Vector4D& thirdRow,
					 const Vector4D& fourthRow);
			Matrix4D(float diagonal);
			Matrix4D(const Matrix4D& matrix);

			~Matrix4D() = default;

			Matrix4D Inverted() const;
			Matrix4D& Invert();
			Matrix4D Transposed() const;
			Matrix4D& Transpose();
			float Determinant() const;
			Vector4D GetColumn(int columnIndex) const;
			void SetColumn(int columnIndex, const Vector4D& vector);
			Vector4D GetRow(int rowIndex) const;
			void SetRow(int rowIndex, const Vector4D& vector);
			Vector3D GetTranslation() const;
			void SetTranslation(const Vector4D& translation);
			Matrix3D AffineMatrix() const;
			Matrix3D NormalMatrix() const;

			static Matrix4D MakeRotationX(float angle);
			static Matrix4D MakeRotationY(float angle);
			static Matrix4D MakeRotationZ(float angle);
			static Matrix4D MakeRotaion(const float angle, const Vector3D& axis);
			static Matrix4D MakeScale(float uniformScale);
			static Matrix4D MakeScale(float scaleX, float scaleY, float scaleZ);
			static Matrix4D MakeScale(const Vector3D& vector);
			static Matrix4D MakeTranslation(float uniformTranslation);
			static Matrix4D MakeTranslation(float translationX, float translationY, float translationZ);
			static Matrix4D MakeTranslation(const Vector3D& vector);
			static Matrix4D LookAt(const Vector3D& cameraPosition, const Vector3D& target, const Vector3D& up);
			static Matrix4D Orthographic(float left, float right, float bottom , float top, float near, float far);
			static Matrix4D Perspective(float fieldOfViewInDegrees, float aspectRatio, float near, float far);
			static Matrix4D Identity();

			Matrix4D& operator=(const Matrix4D& matrix);

			const float& operator()(int rowIndex, int columnIndex) const;
			float& operator()(int rowIndex, int columnIndex);

			Matrix4D& operator*=(const Matrix4D& matrix);
			Vector4D operator*=(const Vector4D& vector);
			Matrix4D& operator*=(const float scalar);
		};

		Matrix4D operator*(const Matrix4D& leftMatrix, const Matrix4D& rightMatrix);
		Vector4D operator*(const Matrix4D& matrix, const Vector4D& vector);
		Matrix4D operator*(const Matrix4D& matrix, float scalar);

		std::ostream& operator<<(std::ostream& stream, const Matrix4D& matrix);
	}
}
