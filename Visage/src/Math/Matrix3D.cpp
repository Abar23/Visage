#include <utility>
#include <cstring>
#include <cmath>
#include "Matrix3D.h"
#include "MathFunctions.h"

namespace Visage
{
	namespace Math
	{
		Matrix3D::Matrix3D()
			: entries{ 0.0f }
		{
		}

		Matrix3D::Matrix3D(float m00, float m01, float m02, 
						   float m10, float m11, float m12, 
						   float m20, float m21, float m22)
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

		Matrix3D::Matrix3D(const Vector3D& firstColumn, const Vector3D& secondColumn, const Vector3D& thirdColumn)
		{
			// Column-major ordering
			entries[0][0] = firstColumn.x;
			entries[0][1] = firstColumn.y;
			entries[0][2] = firstColumn.z;

			entries[1][0] = secondColumn.x;
			entries[1][1] = secondColumn.y;
			entries[1][2] = secondColumn.z;

			entries[2][0] = thirdColumn.x;
			entries[2][1] = thirdColumn.y;
			entries[2][2] = thirdColumn.z;
		}

		Matrix3D::Matrix3D(const Matrix3D& matrix)
		{
			std::memcpy(entries, matrix.entries, 9 * sizeof(float));
		}

		Matrix3D Matrix3D::Inverse() const
		{
			Vector3D firstColumn = GetColumn(0);
			Vector3D secondColumn = GetColumn(1);
			Vector3D thirdColumn = GetColumn(2);

			Vector3D firstRow = Vector3D::Cross(secondColumn, thirdColumn);
			Vector3D secondRow = Vector3D::Cross(thirdColumn, firstColumn);
			Vector3D thirdRow = Vector3D::Cross(firstColumn, secondColumn);

			float inverseDet = 1.0f / Vector3D::Dot(thirdRow, thirdColumn);

			return Matrix3D(firstRow.x * inverseDet, secondRow.x * inverseDet, thirdRow.x * inverseDet, 
							firstRow.y * inverseDet, secondRow.y * inverseDet, thirdRow.y * inverseDet,
							firstRow.z * inverseDet, secondRow.z * inverseDet, thirdRow.z * inverseDet);
		}

		Matrix3D Matrix3D::Transpose() const
		{
			return Matrix3D(entries[0][0], entries[0][1], entries[0][2], 
							entries[1][0], entries[1][1], entries[1][2], 
							entries[2][0], entries[2][1], entries[2][2]);
		}

		float Matrix3D::Determinant() const
		{
			return entries[0][0] * (entries[1][1] * entries[2][2] - entries[2][1] * entries[1][2])
				   + entries[1][0] * (entries[2][1] * entries[0][2] - entries[0][1] * entries[2][2])
				   + entries[2][0] * (entries[0][1] * entries[1][2] - entries[1][1] * entries[0][2]);
		}

		Vector3D Matrix3D::GetRow(int rowIndex) const
		{
			return Vector3D(entries[0][rowIndex], entries[1][rowIndex], entries[2][rowIndex]);
		}

		Vector3D Matrix3D::GetColumn(int columnIndex) const
		{
			return columns[columnIndex];
		}

		Matrix3D Matrix3D::MakeRotationX(const float angle)
		{
			float radians = DegreesToRad(angle);
			float cos = std::cos(radians);
			float sin = std::sin(radians);

			return Matrix3D(1.0f, 0.0f, 0.0f,
							0.0f, cos, -sin,
							0.0f, sin, cos);
		}

		Matrix3D Matrix3D::MakeRotationY(const float angle)
		{
			float radians = DegreesToRad(angle);
			float cos = std::cos(radians);
			float sin = std::sin(radians);

			return Matrix3D(cos, 0.0f, sin,
							0.0f, 1.0f, 0.0f,
							-sin, 0.0f, cos);
		}

		Matrix3D Matrix3D::MakeRotationZ(const float angle)
		{
			float radians = DegreesToRad(angle);
			float cos = std::cos(radians);
			float sin = std::sin(radians);

			return Matrix3D(cos, -sin, 0.0f,
							sin, cos, 0.0f,
							0.0f, 0.0f, 1.0f);
		}

		Matrix3D Matrix3D::MakeRotaion(const float angle, const Vector3D& axis)
		{
			float radians = DegreesToRad(angle);
			float cos = std::cos(radians);
			float sin = std::sin(radians);
			float oneMinsCos = 1.0f - cos;

			float x = axis.x * oneMinsCos;
			float y = axis.y * oneMinsCos;
			float z = axis.z * oneMinsCos;
			float axisXAxisY = x * axis.y;
			float axisXAxisZ = x * axis.z;
			float axisYAxisZ = y * axis.z;

			return Matrix3D(cos + x * axis.x, axisXAxisY - sin * axis.z, axisXAxisZ + sin * axis.y,
							axisXAxisY + sin * axis.z, cos + y * axis.y, axisYAxisZ - sin * axis.x,
							axisXAxisZ - sin * axis.y, axisYAxisZ + sin * axis.x, cos + z * axis.z);
		}

		Matrix3D Matrix3D::MakeScale(const float scale)
		{
			return Matrix3D(scale, 0.0f, 0.0f,
							0.0f, scale, 0.0f,
							0.0f, 0.0f, scale);
		}

		Matrix3D Matrix3D::MakeScale(const float scaleX, const float scaleY, const float scaleZ)
		{
			return Matrix3D(scaleX, 0.0f, 0.0f,
							0.0f, scaleY, 0.0f,
							0.0f, 0.0f, scaleZ);
		}

		Matrix3D Matrix3D::MakeScale(const Vector3D& vector)
		{
			return Matrix3D(vector.x, 0.0f, 0.0f,
							0.0f, vector.y, 0.0f,
							0.0f, 0.0f, vector.z);
		}

		Matrix3D Matrix3D::Identity()
		{
			return Matrix3D(1.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f,
							0.0f, 0.0f, 1.0f);
		}

		Matrix3D& Matrix3D::operator=(const Matrix3D& matrix)
		{
			std::memcpy(entries, matrix.entries, 9 * sizeof(float));
			return *this;
		}

		const float& Matrix3D::operator()(const int rowIndex, const int columnIndex) const
		{
			return entries[rowIndex][columnIndex];
		}

		float& Matrix3D::operator()(const int rowIndex, const int columnIndex)
		{
			return entries[rowIndex][columnIndex];
		}

		Matrix3D& Matrix3D::operator*=(const Matrix3D& matrix)
		{
			entries[0][0] = entries[0][0] * matrix.entries[0][0] + entries[1][0] * matrix.entries[0][1] * entries[2][0] + entries[0][2];
			entries[0][1] = entries[0][0] * matrix.entries[1][0] + entries[1][0] * matrix.entries[1][1] * entries[2][0] + entries[1][2];
			entries[0][2] = entries[0][0] * matrix.entries[2][0] + entries[1][0] * matrix.entries[2][1] * entries[2][0] + entries[2][2];
						   
			entries[1][0] = entries[0][1] * matrix.entries[0][0] + entries[1][1] * matrix.entries[0][1] * entries[2][1] + entries[0][2];
			entries[1][1] = entries[0][1] * matrix.entries[1][0] + entries[1][1] * matrix.entries[1][1] * entries[2][1] + entries[1][2];
			entries[1][2] = entries[0][1] * matrix.entries[2][0] + entries[1][1] * matrix.entries[2][1] * entries[2][1] + entries[2][2];
						   
			entries[2][0] = entries[0][2] * matrix.entries[0][0] + entries[1][2] * matrix.entries[0][1] * entries[2][2] + entries[0][2];
			entries[2][1] = entries[0][2] * matrix.entries[1][0] + entries[1][2] * matrix.entries[1][1] * entries[2][2] + entries[1][2];
			entries[2][2] = entries[0][2] * matrix.entries[2][0] + entries[1][2] * matrix.entries[2][1] * entries[2][2] + entries[2][2];

			return *this;
		}

		Vector3D Matrix3D::operator*=(const Vector3D& vector)
		{
			return Vector3D(entries[0][0] * vector.x + entries[1][0] * vector.y + entries[2][0] * vector.z,
							entries[0][1] * vector.x + entries[1][1] * vector.y + entries[2][1] * vector.z,
							entries[0][2] * vector.x + entries[1][2] * vector.y + entries[2][2] * vector.z);
		}

		Matrix3D& Matrix3D::operator*=(const float scalar)
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

		Matrix3D operator*(const Matrix3D& leftMatrix, const Matrix3D& rightMatrix)
		{
			Matrix3D leftMatrixCopy = leftMatrix;
			return leftMatrixCopy *= rightMatrix;
		}

		Vector3D operator*(const Matrix3D& matrix, const Vector3D& vector)
		{
			Matrix3D matrixCopy = matrix;
			return matrixCopy *= vector;
		}

		Matrix3D operator*(const Matrix3D& matrix, const float scalar)
		{
			Matrix3D matrixCopy = matrix;
			return matrixCopy *= scalar;
		}

		std::ostream& operator<<(std::ostream& stream, const Matrix3D& matrix)
		{
			stream << "[ " << matrix(0, 0) << ", " << matrix(0, 1) << ", " << matrix(0, 2) << " ]" << std::endl;
			stream << "[ " << matrix(1, 0) << ", " << matrix(1, 1) << ", " << matrix(1, 2) << " ]" << std::endl;
			stream << "[ " << matrix(2, 0) << ", " << matrix(2, 1) << ", " << matrix(2, 2) << " ]" << std::endl;
			return stream;
		}
	}
}
