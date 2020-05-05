#pragma once

#include "Vec4.h"
#include "Mat3.h"

namespace Visage
{
	namespace Math
	{
		class Mat4
		{
		protected:
			float entries[4][4];

		public:
			Mat4();
			Mat4(float m00, float m01, float m02, float m03,
				 float m10, float m11, float m12, float m13,
				 float m20, float m21, float m22, float m23,
				 float m30, float m31, float m32, float m33);
			Mat4(const Vec4& firstRow,
				 const Vec4& secondRow,
				 const Vec4& thirdRow,
				 const Vec4& fourthRow);
			Mat4(float diagonal);
			Mat4(const Mat4& matrix);

			~Mat4() = default;

			Mat4 Inverted() const;
			Mat4& Invert();
			Mat4 Transposed() const;
			Mat4& Transpose();
			float Determinant() const;
			Vec4 GetColumn(int columnIndex) const;
			void SetColumn(int columnIndex, const Vec4& vector);
			Vec4 GetRow(int rowIndex) const;
			void SetRow(int rowIndex, const Vec4& vector);
			Vec3 GetTranslation() const;
			void SetTranslation(const Vec4& translation);
			Mat3 AffineMatrix() const;
			Mat3 NormalMatrix() const;

			static Mat4 MakeRotationX(float angle);
			static Mat4 MakeRotationY(float angle);
			static Mat4 MakeRotationZ(float angle);
			static Mat4 MakeRotation(const float angle, const Vec3& axis);
			static Mat4 MakeScale(float uniformScale);
			static Mat4 MakeScale(float scaleX, float scaleY, float scaleZ);
			static Mat4 MakeScale(const Vec3& vector);
			static Mat4 MakeTranslation(float uniformTranslation);
			static Mat4 MakeTranslation(float translationX, float translationY, float translationZ);
			static Mat4 MakeTranslation(const Vec3& vector);
			static Mat4 LookAt(const Vec3& cameraPosition, const Vec3& targetPosition, const Vec3& up);
			static Mat4 Orthographic(float left, float right, float bottom , float top, float near, float far);
			static Mat4 Perspective(float fieldOfViewInDegrees, float aspectRatio, float near, float far);
			static Mat4 Identity();

			Mat4& operator=(const Mat4& matrix);

			inline const float& operator()(int rowIndex, int columnIndex) const
			{
				return entries[columnIndex][rowIndex];
			}

			inline float& operator()(int rowIndex, int columnIndex)
			{
				return entries[columnIndex][rowIndex];
			}

			Mat4& operator*=(const Mat4& matrix);
			Mat4& operator*=(const float scalar);
		};

		Mat4 operator*(const Mat4& leftMatrix, const Mat4& rightMatrix);
		Vec4 operator*(const Mat4& matrix, const Vec4& vector);
		Mat4 operator*(const Mat4& matrix, float scalar);

		std::ostream& operator<<(std::ostream& stream, const Mat4& matrix);
	}
}
