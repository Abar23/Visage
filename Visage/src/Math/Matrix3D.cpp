#include <utility>
#include <cstring>
#include "Matrix3D.h"

namespace Visage
{
	namespace Math
	{
		Matrix3D::Matrix3D()
			: matrixData{ 0 }
		{
		}

		Matrix3D::Matrix3D(float m00, float m01, float m02, 
						   float m10, float m11, float m12, 
						   float m20, float m21, float m22)
		{
			// Column-major ordering
			matrixData[0][0] = m00;
			matrixData[0][1] = m10;
			matrixData[0][2] = m20;

			matrixData[1][0] = m01;
			matrixData[1][1] = m11;
			matrixData[1][2] = m21;

			matrixData[1][0] = m02;
			matrixData[1][1] = m12;
			matrixData[1][2] = m22;
		}

		Matrix3D::Matrix3D(const Vector3D& firstColumn, const Vector3D& secondColumn, const Vector3D& thirdColumn)
		{
			// Column-major ordering
			matrixData[0][0] = firstColumn.x;
			matrixData[0][1] = firstColumn.y;
			matrixData[0][2] = firstColumn.z;

			matrixData[1][0] = secondColumn.x;
			matrixData[1][1] = secondColumn.y;
			matrixData[1][2] = secondColumn.z;

			matrixData[1][0] = thirdColumn.x;
			matrixData[1][1] = thirdColumn.y;
			matrixData[1][2] = thirdColumn.z;
		}

		Matrix3D::Matrix3D(const Matrix3D& matrix)
		{
			std::memcpy(matrixData, matrix.matrixData, 9 * sizeof(float));
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

			return Matrix3D(firstRow.x * inverseDet, firstRow.y * inverseDet, firstRow.z * inverseDet, 
							secondRow.x * inverseDet, secondRow.y * inverseDet, secondRow.z * inverseDet,
							thirdRow.x * inverseDet, thirdRow.y * inverseDet, thirdRow.z * inverseDet);
		}

		Matrix3D Matrix3D::Transpose() const
		{
			return Matrix3D(matrixData[0][0], matrixData[0][1], matrixData[0][2], 
							matrixData[1][0], matrixData[1][1], matrixData[1][2], 
							matrixData[2][0], matrixData[2][1], matrixData[2][2]);
		}

		float Matrix3D::Determinant() const
		{
			return matrixData[0][0] * (matrixData[1][1] * matrixData[2][2] - matrixData[2][1] * matrixData[1][2])
				   + matrixData[1][0] * (matrixData[0][1] * matrixData[2][2] - matrixData[2][1] * matrixData[0][2])
				   + matrixData[2][0] * (matrixData[0][1] * matrixData[1][2] - matrixData[2][1] * matrixData[0][2]);
		}

		Vector3D Matrix3D::GetRow(int rowIndex) const
		{
			return rows[rowIndex];
		}

		Vector3D Matrix3D::GetColumn(int columnIndex) const
		{
			return *reinterpret_cast<Vector3D*>(&matrixData[columnIndex]);
		}

		Matrix3D Matrix3D::MakeRotationX(const float angle)
		{
			return Matrix3D();
		}

		Matrix3D Matrix3D::MakeRotationY(const float angle)
		{
			return Matrix3D();
		}

		Matrix3D Matrix3D::MakeRotationZ(const float angle)
		{
			return Matrix3D();
		}

		Matrix3D Matrix3D::MakeRotaion(const float angle, const Vector3D& axis)
		{
			return Matrix3D();
		}

		Matrix3D Matrix3D::MakeScale(const float scaleX, const float scaleY, const float scaleZ)
		{
			return Matrix3D();
		}

		Matrix3D Matrix3D::MakeScale(const Vector3D& vector)
		{
			return Matrix3D();
		}

		Matrix3D Matrix3D::Identity()
		{
			return Matrix3D();
		}

		Matrix3D& Matrix3D::operator=(const Matrix3D& matrix)
		{
			// TODO: insert return statement here
		}

		const float& Matrix3D::operator()(const int rowIndex, const int columnIndex) const
		{
			return matrixData[rowIndex][columnIndex];
		}

		float& Matrix3D::operator()(const int rowIndex, const int columnIndex)
		{
			return matrixData[rowIndex][columnIndex];
		}

		Matrix3D& Matrix3D::operator*=(const Matrix3D& matrix)
		{
			// TODO: insert return statement here
		}

		Matrix3D& Matrix3D::operator*=(const Vector3D& vector)
		{
			// TODO: insert return statement here
		}

		Matrix3D& Matrix3D::operator*=(const float scalar)
		{
			// TODO: insert return statement here
		}

		Matrix3D operator*(const Matrix3D& leftMatrix, const Matrix3D& rightMatrix)
		{
			return Matrix3D();
		}

		Vector3D operator*(const Matrix3D& leftMatrix, const Vector3D& rightMatrix)
		{
			return Vector3D();
		}

		Matrix3D operator*(const Matrix3D& matrix, const float scalar)
		{
			return Matrix3D();
		}

		std::ostream& operator<<(std::ostream& stream, const Matrix3D& matrix)
		{
			stream << "Matrix4D: ( " << matrix(0, 0) << ", " << matrix(0, 1) << ", " << matrix(0, 2) << std::endl;
			stream << matrix(1, 0) << ", " << matrix(1, 1) << ", " << matrix(1, 2) << std::endl;
			stream << matrix(1, 0) << ", " << matrix(1, 1) << ", " << matrix(1, 2) << ")" << std::endl;
		}
	}
}
