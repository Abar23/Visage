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
			Mat3x4(float m00, float m01, float m02, float m03,
				   float m10, float m11, float m12, float m13,
				   float m20, float m21, float m22, float m23);
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
			Vec3 GetColumn(int columnIndex) const;
			void SetColumn(int columnIndex, const Vec3& vector);
			Vec4 GetRow(int rowIndex) const;
			void SetRow(int rowIndex, const Vec4& vector);
			Vec3 GetTranslation() const;
			void SetTranslation(const Vec3& translation);
			Mat3 AffineMatrix() const;
			Mat3 NormalMatrix() const;
			Mat4 ToMat4() const;

			static Mat3x4 MakeRotationX(float angle);
			static Mat3x4 MakeRotationY(float angle);
			static Mat3x4 MakeRotationZ(float angle);
			static Mat3x4 MakeRotation(const float angle, const Vec3& axis);
			static Mat3x4 MakeScale(float uniformScale);
			static Mat3x4 MakeScale(float scaleX, float scaleY, float scaleZ);
			static Mat3x4 MakeScale(const Vec3& vector);
			static Mat3x4 MakeTranslation(float uniformTranslation);
			static Mat3x4 MakeTranslation(float translationX, float translationY, float translationZ);
			static Mat3x4 MakeTranslation(const Vec3& vector);
			static Mat3x4 LookAt(const Vec3& cameraPosition, const Vec3& targetPosition, const Vec3& up);
			static Mat3x4 Orthographic(float left, float right, float bottom, float top, float near, float far);
			static Mat3x4 Identity();

			Mat3x4& operator=(const Mat3x4& matrix);

			inline const float& operator()(int rowIndex, int columnIndex) const
			{
				return entries[columnIndex][rowIndex];
			}

			inline float& operator()(int rowIndex, int columnIndex)
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
		Mat3x4 operator*(const Mat3x4& matrix, float scalar);

		std::ostream& operator<<(std::ostream& stream, const Mat3x4& matrix);
	}
}