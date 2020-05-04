#pragma once

#include <ostream>
#include "Vec3.h"

namespace Visage
{
	namespace Math
	{
		class Mat3
		{
		private:
			float entries[3][3];

		public:
			Mat3();
			Mat3(float m00, float m01, float m02,
				float m10, float m11, float m12,
				float m20, float m21, float m22);
			Mat3(const Vec3& firstRow, 
				 const Vec3& secondRow, 
				 const Vec3& thirdRow);
			Mat3(float diagonal);
			Mat3(const Mat3& matrix);

			~Mat3() = default;

			Mat3 Inverted() const;
			Mat3& Invert();
			Mat3 Transposed() const;
			Mat3& Transpose();
			float Determinant() const;
			Vec3 GetColumn(int columnIndex) const;
			void SetColumn(int columnIndex, const Vec3& vector);
			Vec3 GetRow(int rowIndex) const;
			void SetRow(int rowIndex, const Vec3& vector);

			static Mat3 MakeRotationX(float angle);
			static Mat3 MakeRotationY(float angle);
			static Mat3 MakeRotationZ(float angle);
			static Mat3 MakeRotation(float angle, const Vec3& axis);
			static Mat3 MakeScale(float uniformScale);
			static Mat3 MakeScale(float scaleX, float scaleY, float scaleZ);
			static Mat3 MakeScale(const Vec3& vector);
			static Mat3 Identity();

			Mat3& operator=(const Mat3& matrix);
			
			const float& operator()(int rowIndex, int columnIndex) const;
			float& operator()(int rowIndex, int columnIndex);

			Mat3& operator*=(const Mat3& matrix);
			Vec3 operator*=(const Vec3& vector);
			Mat3& operator*=(const float scalar);
		};

		Mat3 operator*(const Mat3& leftMatrix, const Mat3& rightMatrix);
		Vec3 operator*(const Mat3& matrix, const Vec3& vector);
		Mat3 operator*(const Mat3& matrix, float scalar);

		std::ostream& operator<<(std::ostream& stream, const Mat3& matrix);
	}
}
