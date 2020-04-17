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

		Matrix3D::Matrix3D(const Vector3D& firstRow, const Vector3D& secondRow, const Vector3D& thirdRow)
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

		Matrix3D::Matrix3D(float diagonal)
			: entries{ 0.0f }
		{
			entries[0][0] = diagonal;
			entries[1][1] = diagonal;
			entries[2][2] = diagonal;
		}

		Matrix3D::Matrix3D(const Matrix3D& matrix)
		{
			std::memcpy(entries, matrix.entries, sizeof(Matrix3D));
		}

		Matrix3D Matrix3D::Inverse() const
		{
			Vector3D a = columns[0];
			Vector3D b = columns[1];
			Vector3D c = columns[2];

			Vector3D bCrossC = Vector3D::Cross(b, c);
			Vector3D cCrossa = Vector3D::Cross(c, a);
			Vector3D aCrossb = Vector3D::Cross(a, b);

			float inverseDet = 1.0f / Vector3D::Dot(aCrossb, c);

			return Matrix3D(bCrossC.x * inverseDet, bCrossC.y * inverseDet, bCrossC.z * inverseDet, 
							cCrossa.x * inverseDet, cCrossa.y * inverseDet, cCrossa.z * inverseDet,
							aCrossb.x * inverseDet, aCrossb.y * inverseDet, aCrossb.z * inverseDet);
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

		Matrix3D Matrix3D::MakeRotationX(float angle)
		{
			float radians = DegreesToRad(angle);
			float cos = std::cos(radians);
			float sin = std::sin(radians);

			return Matrix3D(1.0f, 0.0f, 0.0f,
							0.0f, cos, -sin,
							0.0f, sin, cos);
		}

		Matrix3D Matrix3D::MakeRotationY(float angle)
		{
			float radians = DegreesToRad(angle);
			float cos = std::cos(radians);
			float sin = std::sin(radians);

			return Matrix3D(cos, 0.0f, sin,
							0.0f, 1.0f, 0.0f,
							-sin, 0.0f, cos);
		}

		Matrix3D Matrix3D::MakeRotationZ(float angle)
		{
			float radians = DegreesToRad(angle);
			float cos = std::cos(radians);
			float sin = std::sin(radians);

			return Matrix3D(cos, -sin, 0.0f,
							sin, cos, 0.0f,
							0.0f, 0.0f, 1.0f);
		}

		Matrix3D Matrix3D::MakeRotaion(float angle, const Vector3D& axis)
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

		Matrix3D Matrix3D::MakeScale(float uniformScale)
		{
			return Matrix3D(uniformScale, 0.0f, 0.0f,
							0.0f, uniformScale, 0.0f,
							0.0f, 0.0f, uniformScale);
		}

		Matrix3D Matrix3D::MakeScale(float scaleX, float scaleY, float scaleZ)
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
			return Matrix3D(1.0f);
		}

		Matrix3D& Matrix3D::operator=(const Matrix3D& matrix)
		{
			std::memcpy(entries, matrix.entries, sizeof(Matrix3D));
			return *this;
		}

		const float& Matrix3D::operator()(int rowIndex, int columnIndex) const
		{
			return entries[columnIndex][rowIndex];
		}

		float& Matrix3D::operator()(int rowIndex, int columnIndex)
		{
			return entries[columnIndex][rowIndex];
		}

		Matrix3D& Matrix3D::operator*=(const Matrix3D& matrix)
		{
			entries[0][0] = entries[0][0] * matrix.entries[0][0] + entries[1][0] * matrix.entries[0][1] + entries[2][0] * entries[0][2];
			entries[0][1] = entries[0][0] * matrix.entries[1][0] + entries[1][0] * matrix.entries[1][1] + entries[2][0] * entries[1][2];
			entries[0][2] = entries[0][0] * matrix.entries[2][0] + entries[1][0] * matrix.entries[2][1] + entries[2][0] * entries[2][2];
						   
			entries[1][0] = entries[0][1] * matrix.entries[0][0] + entries[1][1] * matrix.entries[0][1] + entries[2][1] * entries[0][2];
			entries[1][1] = entries[0][1] * matrix.entries[1][0] + entries[1][1] * matrix.entries[1][1] + entries[2][1] * entries[1][2];
			entries[1][2] = entries[0][1] * matrix.entries[2][0] + entries[1][1] * matrix.entries[2][1] + entries[2][1] * entries[2][2];
						   
			entries[2][0] = entries[0][2] * matrix.entries[0][0] + entries[1][2] * matrix.entries[0][1] + entries[2][2] * entries[0][2];
			entries[2][1] = entries[0][2] * matrix.entries[1][0] + entries[1][2] * matrix.entries[1][1] + entries[2][2] * entries[1][2];
			entries[2][2] = entries[0][2] * matrix.entries[2][0] + entries[1][2] * matrix.entries[2][1] + entries[2][2] * entries[2][2];

			return *this;
		}

		Vector3D Matrix3D::operator*=(const Vector3D& vector)
		{
			return Vector3D(entries[0][0] * vector.x + entries[1][0] * vector.y + entries[2][0] * vector.z,
							entries[0][1] * vector.x + entries[1][1] * vector.y + entries[2][1] * vector.z,
							entries[0][2] * vector.x + entries[1][2] * vector.y + entries[2][2] * vector.z);
		}

		Matrix3D& Matrix3D::operator*=(float scalar)
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

		Matrix3D operator*(const Matrix3D& matrix, float scalar)
		{
			Matrix3D matrixCopy = matrix;
			return matrixCopy *= scalar;
		}

		std::ostream& operator<<(std::ostream& stream, const Matrix3D& matrix)
		{
			stream << "( " << matrix(0, 0) << ", " << matrix(0, 1) << ", " << matrix(0, 2) << std::endl;
			stream << "  " << matrix(1, 0) << ", " << matrix(1, 1) << ", " << matrix(1, 2) << std::endl;
			stream << "  " << matrix(2, 0) << ", " << matrix(2, 1) << ", " << matrix(2, 2) << " )";
			return stream;
		}
	}
}
