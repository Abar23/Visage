#include <utility>
#include <cstring>
#include <cmath>
#include "Mat3.h"
#include "MathFunctions.h"

namespace Visage
{
	namespace Math
	{
		Mat3::Mat3()
			: entries{ 0.0f }
		{
		}

		Mat3::Mat3(const float m00, const float m01, const float m02, 
				   const float m10, const float m11, const float m12, 
				   const float m20, const float m21, const float m22)
		{
			// Column-major ordering
			entries[0][0] = m00;
			entries[0][1] = m10;
			entries[0][2] = m20;

			entries[1][0] = m01;
			entries[1][1] = m11;
			entries[1][2] = m21;

			entries[2][0] = m02;
			entries[2][1] = m12;
			entries[2][2] = m22;
		}

		Mat3::Mat3(const Vec3& firstRow,
				   const Vec3& secondRow, 
				   const Vec3& thirdRow)
		{
			// Column-major ordering
			entries[0][0] = firstRow.x;
			entries[1][0] = firstRow.y;
			entries[2][0] = firstRow.z;

			entries[0][1] = secondRow.x;
			entries[1][1] = secondRow.y;
			entries[2][1] = secondRow.z;

			entries[0][2] = thirdRow.x;
			entries[1][2] = thirdRow.y;
			entries[2][2] = thirdRow.z;
		}

		Mat3::Mat3(const float diagonal)
			: entries{ 0.0f }
		{
			entries[0][0] = diagonal;
			entries[1][1] = diagonal;
			entries[2][2] = diagonal;
		}

		Mat3::Mat3(const Mat3& matrix)
		{
			std::memcpy(entries, matrix.entries, sizeof(Mat3));
		}

		Mat3 Mat3::Inverted() const
		{
			const Vec3 a = reinterpret_cast<const Vec3&>(entries[0]);
			const Vec3 b = reinterpret_cast<const Vec3&>(entries[1]);
			const Vec3 c = reinterpret_cast<const Vec3&>(entries[2]);

			Vec3 bCrossC = Vec3::Cross(b, c);
			Vec3 cCrossa = Vec3::Cross(c, a);
			Vec3 aCrossb = Vec3::Cross(a, b);

			float inverseDet = 1.0f / Vec3::Dot(aCrossb, c);

			return Mat3(bCrossC.x * inverseDet, bCrossC.y * inverseDet, bCrossC.z * inverseDet, 
						cCrossa.x * inverseDet, cCrossa.y * inverseDet, cCrossa.z * inverseDet,
						aCrossb.x * inverseDet, aCrossb.y * inverseDet, aCrossb.z * inverseDet);
		}

		Mat3& Mat3::Invert()
		{
			const Vec3 a = reinterpret_cast<const Vec3&>(entries[0]);
			const Vec3 b = reinterpret_cast<const Vec3&>(entries[1]);
			const Vec3 c = reinterpret_cast<const Vec3&>(entries[2]);

			Vec3 bCrossC = Vec3::Cross(b, c);
			Vec3 cCrossa = Vec3::Cross(c, a);
			Vec3 aCrossb = Vec3::Cross(a, b);

			float inverseDet = 1.0f / Vec3::Dot(aCrossb, c);

			entries[0][0] = bCrossC.x * inverseDet;
			entries[0][1] = cCrossa.x * inverseDet;
			entries[0][2] = aCrossb.x * inverseDet;

			entries[1][0] = bCrossC.y * inverseDet;
			entries[1][1] = cCrossa.y * inverseDet;
			entries[1][2] = aCrossb.y * inverseDet;

			entries[2][0] = bCrossC.z * inverseDet;
			entries[2][1] = cCrossa.z * inverseDet;
			entries[2][2] = aCrossb.z * inverseDet;
			return *this;
		}

		Mat3 Mat3::Transposed() const
		{
			return Mat3(entries[0][0], entries[0][1], entries[0][2], 
						entries[1][0], entries[1][1], entries[1][2], 
						entries[2][0], entries[2][1], entries[2][2]);
		}

		Mat3& Mat3::Transpose()
		{
			Mat3 temp = *this;

			entries[0][1] = temp.entries[1][0];
			entries[0][2] = temp.entries[2][0];

			entries[1][0] = temp.entries[0][1];
			entries[1][2] = temp.entries[2][1];

			entries[2][0] = temp.entries[0][2];
			entries[2][1] = temp.entries[1][2];

			return *this;
		}

		float Mat3::Determinant() const
		{
			return entries[0][0] * (entries[1][1] * entries[2][2] - entries[2][1] * entries[1][2])
				   + entries[1][0] * (entries[2][1] * entries[0][2] - entries[0][1] * entries[2][2])
				   + entries[2][0] * (entries[0][1] * entries[1][2] - entries[1][1] * entries[0][2]);
		}

		Vec3 Mat3::GetColumn(const int columnIndex) const
		{
			return Vec3(entries[columnIndex][0],
						entries[columnIndex][1],
						entries[columnIndex][2]);
		}

		void Mat3::SetColumn(const int columnIndex, const Vec3& vector)
		{
			entries[columnIndex][0] = vector.x;
			entries[columnIndex][1] = vector.y;
			entries[columnIndex][2] = vector.z;
		}

		Vec3 Mat3::GetRow(const int rowIndex) const
		{
			return Vec3(entries[0][rowIndex], entries[1][rowIndex], entries[2][rowIndex]);
		}

		void Mat3::SetRow(const int rowIndex, const Vec3& vector)
		{
			entries[0][rowIndex] = vector.x;
			entries[1][rowIndex] = vector.y;
			entries[2][rowIndex] = vector.z;
		}

		Mat3 Mat3::MakeRotationX(const float angleInDegrees)
		{
			float radians = DegreesToRad(angleInDegrees);
			float cos = std::cosf(radians);
			float sin = std::sinf(radians);

			return Mat3(1.0f, 0.0f, 0.0f,
						0.0f, cos, -sin,
						0.0f, sin, cos);
		}

		Mat3 Mat3::MakeRotationY(const float angleInDegrees)
		{
			float radians = DegreesToRad(angleInDegrees);
			float cos = std::cosf(radians);
			float sin = std::sinf(radians);

			return Mat3(cos, 0.0f, sin,
						0.0f, 1.0f, 0.0f,
						-sin, 0.0f, cos);
		}

		Mat3 Mat3::MakeRotationZ(const float angleInDegrees)
		{
			float radians = DegreesToRad(angleInDegrees);
			float cos = std::cosf(radians);
			float sin = std::sinf(radians);

			return Mat3(cos, -sin, 0.0f,
						sin, cos, 0.0f,
						0.0f, 0.0f, 1.0f);
		}

		Mat3 Mat3::MakeRotation(const Vec3& axis, const float angleInDegrees)
		{
			float radians = DegreesToRad(angleInDegrees);
			float cos = std::cosf(radians);
			float sin = std::sinf(radians);
			float oneMinsCos = 1.0f - cos;

			float x = axis.x * oneMinsCos;
			float y = axis.y * oneMinsCos;
			float z = axis.z * oneMinsCos;
			float axisXAxisY = x * axis.y;
			float axisXAxisZ = x * axis.z;
			float axisYAxisZ = y * axis.z;

			return Mat3(cos + x * axis.x, axisXAxisY - sin * axis.z, axisXAxisZ + sin * axis.y,
						axisXAxisY + sin * axis.z, cos + y * axis.y, axisYAxisZ - sin * axis.x,
						axisXAxisZ - sin * axis.y, axisYAxisZ + sin * axis.x, cos + z * axis.z);
		}

		Mat3 Mat3::MakeScale(const float uniformScale)
		{
			return Mat3(uniformScale, 0.0f, 0.0f,
						0.0f, uniformScale, 0.0f,
						0.0f, 0.0f, uniformScale);
		}

		Mat3 Mat3::MakeScale(const float scaleX, const float scaleY, const float scaleZ)
		{
			return Mat3(scaleX, 0.0f, 0.0f,
						0.0f, scaleY, 0.0f,
						0.0f, 0.0f, scaleZ);
		}

		Mat3 Mat3::MakeScale(const Vec3& vector)
		{
			return Mat3(vector.x, 0.0f, 0.0f,
						0.0f, vector.y, 0.0f,
						0.0f, 0.0f, vector.z);
		}

		Mat3 Mat3::Identity()
		{
			return Mat3(1.0f);
		}

		Mat3& Mat3::operator=(const Mat3& matrix)
		{
			std::memcpy(entries, matrix.entries, sizeof(Mat3));
			return *this;
		}

		Mat3& Mat3::operator*=(const Mat3& matrix)
		{
			entries[0][0] = entries[0][0] * matrix.entries[0][0] + entries[1][0] * matrix.entries[0][1] + entries[2][0] * matrix.entries[0][2];
			entries[1][0] = entries[0][0] * matrix.entries[1][0] + entries[1][0] * matrix.entries[1][1] + entries[2][0] * matrix.entries[1][2];
			entries[2][0] = entries[0][0] * matrix.entries[2][0] + entries[1][0] * matrix.entries[2][1] + entries[2][0] * matrix.entries[2][2];

			entries[0][1] = entries[0][1] * matrix.entries[0][0] + entries[1][1] * matrix.entries[0][1] + entries[2][1] * matrix.entries[0][2];
			entries[1][1] = entries[0][1] * matrix.entries[1][0] + entries[1][1] * matrix.entries[1][1] + entries[2][1] * matrix.entries[1][2];
			entries[2][1] = entries[0][1] * matrix.entries[2][0] + entries[1][1] * matrix.entries[2][1] + entries[2][1] * matrix.entries[2][2];

			entries[0][2] = entries[0][2] * matrix.entries[0][0] + entries[1][2] * matrix.entries[0][1] + entries[2][2] * matrix.entries[0][2];
			entries[1][2] = entries[0][2] * matrix.entries[1][0] + entries[1][2] * matrix.entries[1][1] + entries[2][2] * matrix.entries[1][2];
			entries[2][2] = entries[0][2] * matrix.entries[2][0] + entries[1][2] * matrix.entries[2][1] + entries[2][2] * matrix.entries[2][2];

			return *this;
		}

		Mat3& Mat3::operator*=(const float scalar)
		{
			entries[0][0] *= scalar;
			entries[0][1] *= scalar;
			entries[0][2] *= scalar;

			entries[1][0] *= scalar;
			entries[1][1] *= scalar;
			entries[1][2] *= scalar;

			entries[2][0] *= scalar;
			entries[2][1] *= scalar;
			entries[2][2] *= scalar;
			
			return *this;
		}

		Mat3 operator*(const Mat3& leftMatrix, const Mat3& rightMatrix)
		{
			Mat3 leftMatrixCopy = leftMatrix;
			return leftMatrixCopy *= rightMatrix;
		}

		Vec3 operator*(const Mat3& matrix, const Vec3& vector)
		{
			return Vec3(matrix(0, 0) * vector.x + matrix(1, 0) * vector.y + matrix(2, 0) * vector.z,
						matrix(0, 1) * vector.x + matrix(1, 1) * vector.y + matrix(2, 1) * vector.z,
						matrix(0, 2) * vector.x + matrix(1, 2) * vector.y + matrix(2, 2) * vector.z);
		}

		Mat3 operator*(const Mat3& matrix, const float scalar)
		{
			Mat3 matrixCopy = matrix;
			return matrixCopy *= scalar;
		}

		std::ostream& operator<<(std::ostream& stream, const Mat3& matrix)
		{
			stream << "( " << matrix(0, 0) << ", " << matrix(0, 1) << ", " << matrix(0, 2) << std::endl;
			stream << "  " << matrix(1, 0) << ", " << matrix(1, 1) << ", " << matrix(1, 2) << std::endl;
			stream << "  " << matrix(2, 0) << ", " << matrix(2, 1) << ", " << matrix(2, 2) << " )";
			return stream;
		}
	}
}
