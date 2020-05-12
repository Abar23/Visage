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
			Mat4(const float m00, const float m01, const float m02, const float m03,
				 const float m10, const float m11, const float m12, const float m13,
				 const float m20, const float m21, const float m22, const float m23,
				 const float m30, const float m31, const float m32, const float m33);
			Mat4(const Vec4& firstRow,
				 const Vec4& secondRow,
				 const Vec4& thirdRow,
				 const Vec4& fourthRow);
			Mat4(const float diagonal);
			Mat4(const Mat4& matrix);

			~Mat4() = default;

			Mat4 Inverted() const;
			Mat4& Invert();
			Mat4 Transposed() const;
			Mat4& Transpose();
			float Determinant() const;
			Vec4 GetColumn(const int columnIndex) const;
			void SetColumn(const int columnIndex, const Vec4& vector);
			Vec4 GetRow(const int rowIndex) const;
			void SetRow(const int rowIndex, const Vec4& vector);
			Vec3 GetTranslation() const;
			void SetTranslation(const Vec3& translation);
			Mat3 AffineMatrix() const;
			Mat3 NormalMatrix() const;

			static Mat4 MakeRotationX(const float angleInDegrees);
			static Mat4 MakeRotationY(const float angleInDegrees);
			static Mat4 MakeRotationZ(const float angleInDegrees);
			static Mat4 MakeRotation(const Vec3& axis, const float angleInDegrees);
			static Mat4 MakeScale(const float uniformScale);
			static Mat4 MakeScale(const float scaleX, const float scaleY, const float scaleZ);
			static Mat4 MakeScale(const Vec3& vector);
			static Mat4 MakeTranslation(const float uniformTranslation);
			static Mat4 MakeTranslation(const float translationX, const float translationY, const float translationZ);
			static Mat4 MakeTranslation(const Vec3& vector);
			static Mat4 LookAt(const Vec3& cameraPosition, const Vec3& targetPosition, const Vec3& up);
			static Mat4 Orthographic(const float left, const float right, const float bottom , const float top, const float near, const float far);
			static Mat4 Perspective(const float fieldOfViewInDegrees, const float aspectRatio, const float near, const float far);
			static Mat4 Identity();

			Mat4& operator=(const Mat4& matrix);

			inline const float& operator()(const int rowIndex, const int columnIndex) const
			{
				return entries[columnIndex][rowIndex];
			}

			inline float& operator()(const int rowIndex, const int columnIndex)
			{
				return entries[columnIndex][rowIndex];
			}

			Mat4& operator*=(const Mat4& matrix);
			Mat4& operator*=(const float scalar);
		};

		Mat4 operator*(const Mat4& leftMatrix, const Mat4& rightMatrix);
		Vec4 operator*(const Mat4& matrix, const Vec4& vector);
		Mat4 operator*(const Mat4& matrix, const float scalar);

		std::ostream& operator<<(std::ostream& stream, const Mat4& matrix);
	}
}
