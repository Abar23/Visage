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
			Mat3(const float m00, const float m01, const float m02,
				 const float m10, const float m11, const float m12,
				 const float m20, const float m21, const float m22);
			Mat3(const Vec3& firstRow, 
				 const Vec3& secondRow, 
				 const Vec3& thirdRow);
			Mat3(const float diagonal);
			Mat3(const Mat3& matrix);

			~Mat3() = default;

			Mat3 Inverted() const;
			Mat3& Invert();
			Mat3 Transposed() const;
			Mat3& Transpose();
			float Determinant() const;
			Vec3 GetColumn(const int columnIndex) const;
			void SetColumn(const int columnIndex, const Vec3& vector);
			Vec3 GetRow(const int rowIndex) const;
			void SetRow(const int rowIndex, const Vec3& vector);

			static Mat3 MakeRotationX(const float angleInDegrees);
			static Mat3 MakeRotationY(const float angleInDegrees);
			static Mat3 MakeRotationZ(const float angleInDegrees);
			static Mat3 MakeRotation(const Vec3& axis, const float angleInDegrees);
			static Mat3 MakeScale(const float uniformScale);
			static Mat3 MakeScale(const float scaleX, const float scaleY, const float scaleZ);
			static Mat3 MakeScale(const Vec3& vector);
			static Mat3 Identity();

			Mat3& operator=(const Mat3& matrix);
			
			inline const float& operator()(const int rowIndex, const int columnIndex) const
			{
				return entries[columnIndex][rowIndex];
			}

			inline float& operator()(const int rowIndex, const int columnIndex)
			{
				return entries[columnIndex][rowIndex];
			}

			Mat3& operator*=(const Mat3& matrix);
			Mat3& operator*=(const float scalar);
		};

		Mat3 operator*(const Mat3& leftMatrix, const Mat3& rightMatrix);
		Vec3 operator*(const Mat3& matrix, const Vec3& vector);
		Mat3 operator*(const Mat3& matrix, const float scalar);

		std::ostream& operator<<(std::ostream& stream, const Mat3& matrix);
	}
}
