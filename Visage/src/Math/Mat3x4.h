#pragma once

#include "Vec4.h"
#include "Mat3.h"
#include "Mat4.h"

namespace Visage
{
	namespace Math
	{
		class Mat3x4
		{
		private:
			float entries[4][3];

		public:
			Mat3x4();
			Mat3x4(const float m00, const float m01, const float m02, const float m03,
				   const float m10, const float m11, const float m12, const float m13,
				   const float m20, const float m21, const float m22, const float m23);
			Mat3x4(const Vec4& firstRow,
				   const Vec4& secondRow,
				   const Vec4& thirdRow);
			Mat3x4(float diagonal);
			Mat3x4(const Mat3x4& matrix);

			~Mat3x4() = default;

			Mat3x4 Inverted() const;
			Mat3x4& Invert();
			Mat4 TransposedMat4() const;
			float Determinant() const;
			Vec3 GetColumn(const int columnIndex) const;
			void SetColumn(const int columnIndex, const Vec3& vector);
			Vec4 GetRow(const int rowIndex) const;
			void SetRow(const int rowIndex, const Vec4& vector);
			Vec3 GetTranslation() const;
			void SetTranslation(const Vec3& translation);
			Mat3 AffineMatrix() const;
			Mat3 NormalMatrix() const;
			Mat4 ToMat4() const;

			static Mat3x4 MakeRotationX(const float angleInDegrees);
			static Mat3x4 MakeRotationY(const float angleInDegrees);
			static Mat3x4 MakeRotationZ(const float angleInDegrees);
			static Mat3x4 MakeRotation(const Vec3& axis, const float angleInDegrees);
			static Mat3x4 MakeScale(const float uniformScale);
			static Mat3x4 MakeScale(const float scaleX, const float scaleY, const float scaleZ);
			static Mat3x4 MakeScale(const Vec3& vector);
			static Mat3x4 MakeTranslation(const float uniformTranslation);
			static Mat3x4 MakeTranslation(const float translationX, const float translationY, const float translationZ);
			static Mat3x4 MakeTranslation(const Vec3& vector);
			static Mat3x4 LookAt(const Vec3& cameraPosition, const Vec3& targetPosition, const Vec3& up);
			static Mat3x4 Orthographic(const float left, const float right, const float bottom, const float top, const float near, const float far);
			static Mat3x4 Identity();

			Mat3x4& operator=(const Mat3x4& matrix);

			inline const float& operator()(const int rowIndex, const int columnIndex) const
			{
				return entries[columnIndex][rowIndex];
			}

			inline float& operator()(const int rowIndex, const int columnIndex)
			{
				return entries[columnIndex][rowIndex];
			}

			Mat3x4& operator*=(const Mat3x4& matrix);
			Mat3x4& operator*=(const float scalar);
		};

		Mat3x4 operator*(const Mat3x4& leftMatrix, const Mat3x4& rightMatrix);
		Mat4 operator*(const Mat3x4& leftMatrix, const Mat4& rightMatrix);
		Mat4 operator*(const Mat4& leftMatrix, const Mat3x4& rightMatrix);
		Vec4 operator*(const Mat3x4& matrix, const Vec4& vector);
		Vec3 operator*(const Mat3x4& matrix, const Vec3& vector);
		Mat3x4 operator*(const Mat3x4& matrix, const float scalar);

		std::ostream& operator<<(std::ostream& stream, const Mat3x4& matrix);
	}
}