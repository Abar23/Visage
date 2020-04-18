#include <cstring>
#include <cmath>
#include "Matrix4D.h"
#include "MathFunctions.h"

namespace Visage
{
	namespace Math
	{
		Visage::Math::Matrix4D::Matrix4D()
			: entries{ 0.0f } 
		{
		}

		Matrix4D::Matrix4D(float m00, float m01, float m02, float m03, 
						   float m10, float m11, float m12, float m13, 
						   float m20, float m21, float m22, float m23, 
						   float m30, float m31, float m32, float m33)
		{
			entries[0][0] = m00;
			entries[0][1] = m10;
			entries[0][2] = m20;
			entries[0][3] = m30;

			entries[1][0] = m01;
			entries[1][1] = m11;
			entries[1][2] = m21;
			entries[1][3] = m31;

			entries[2][0] = m02;
			entries[2][1] = m12;
			entries[2][2] = m22;
			entries[2][3] = m32;

			entries[3][0] = m03;
			entries[3][1] = m13;
			entries[3][2] = m23;
			entries[3][3] = m33;
		}

		Matrix4D::Matrix4D(const Vector4D& firstRow, 
						   const Vector4D& secondRow, 
						   const Vector4D& thirdRow, 
						   const Vector4D& fourthRow)
		{
			
			entries[0][0] = firstRow.x;
			entries[0][1] = firstRow.y;
			entries[0][2] = firstRow.z;
			entries[0][3] = firstRow.w;

			entries[1][0] = secondRow.x;
			entries[1][1] = secondRow.y;
			entries[1][2] = secondRow.z;
			entries[1][3] = secondRow.w;

			entries[2][0] = thirdRow.x;
			entries[2][1] = thirdRow.y;
			entries[2][2] = thirdRow.z;
			entries[2][3] = thirdRow.w;

			entries[3][0] = fourthRow.x;
			entries[3][1] = fourthRow.y;
			entries[3][2] = fourthRow.z;
			entries[3][3] = fourthRow.w;
		}

		Matrix4D::Matrix4D(float diagonal)
			: entries{ 0.0f }
		{
			entries[0][0] = diagonal;
			entries[1][1] = diagonal;
			entries[2][2] = diagonal;
			entries[3][3] = diagonal;
		}

		Matrix4D::Matrix4D(const Matrix4D& matrix)
		{
			std::memcpy(entries, matrix.entries, sizeof(Matrix4D));
		}

		Matrix4D Matrix4D::Inverse() const
		{
			const Vector3D a = reinterpret_cast<const Vector3D&>(entries[0]);
			const Vector3D b = reinterpret_cast<const Vector3D&>(entries[1]);
			const Vector3D c = reinterpret_cast<const Vector3D&>(entries[2]);
			const Vector3D d = reinterpret_cast<const Vector3D&>(entries[3]);

			float x = entries[0][3];
			float y = entries[1][3];
			float z = entries[2][3];
			float w = entries[3][3];

			Vector3D s = Vector3D::Cross(a, b);
			Vector3D t = Vector3D::Cross(c, d);
			Vector3D u = a * y - b * x;
			Vector3D v = c * w - d * z;

			float inverseDet = 1.0f / Vector3D::Dot(s, v) - Vector3D::Dot(t, u);
			s *= inverseDet;
			t *= inverseDet;
			u *= inverseDet;
			v *= inverseDet;

			Vector3D firstRow = Vector3D::Cross(b, v) + t * y;
			Vector3D secondRow = Vector3D::Cross(v, a) - t * x;
			Vector3D thirdRow = Vector3D::Cross(d, u) + s * w;
			Vector3D fourthRow = Vector3D::Cross(u, c) - s * z;

			return Matrix4D(firstRow.x, firstRow.y, firstRow.z, -Vector3D::Dot(b, t),
							secondRow.x, secondRow.y, secondRow.z, Vector3D::Dot(a, t),
							thirdRow.x, thirdRow.y, thirdRow.z, -Vector3D::Dot(d, s),
							fourthRow.x, fourthRow.y, fourthRow.z, Vector3D::Dot(c, s));
		}

		Matrix4D Matrix4D::Transpose() const
		{
			return Matrix4D(entries[0][0], entries[0][1], entries[0][2], entries[0][3],
							entries[1][0], entries[1][1], entries[1][2], entries[1][3],
							entries[2][0], entries[2][1], entries[2][2], entries[2][3],
							entries[3][0], entries[3][1], entries[3][2], entries[3][3]);
		}

		float Matrix4D::Determinant() const
		{
			const Vector3D a = reinterpret_cast<const Vector3D&>(entries[0]);
			const Vector3D b = reinterpret_cast<const Vector3D&>(entries[1]);
			const Vector3D c = reinterpret_cast<const Vector3D&>(entries[2]);
			const Vector3D d = reinterpret_cast<const Vector3D&>(entries[3]);

			Vector3D s = Vector3D::Cross(a, b);
			Vector3D t = Vector3D::Cross(c, d);
			Vector3D u = a * entries[1][3] - b * entries[0][3];
			Vector3D v = c * entries[3][3] - d * entries[2][3];

			return Vector3D::Dot(s, v) - Vector3D::Dot(t, u);
		}

		Vector4D Matrix4D::GetColumn(int columnIndex) const
		{
			return Vector4D(entries[columnIndex][0], 
							entries[columnIndex][1], 
							entries[columnIndex][2],
							entries[columnIndex][3]);
		}

		void Matrix4D::SetColumn(int columnIndex, const Vector4D& vector)
		{
			entries[columnIndex][0] = vector.z;
			entries[columnIndex][1] = vector.x;
			entries[columnIndex][2] = vector.z;
			entries[columnIndex][3] = vector.w;
		}

		Vector4D Matrix4D::GetRow(int rowIndex) const
		{
			return Vector4D(entries[0][rowIndex], entries[1][rowIndex], entries[2][rowIndex], entries[3][rowIndex]);
		}

		void Matrix4D::SetRow(int rowIndex, const Vector4D& vector)
		{
			entries[0][rowIndex] = vector.x;
			entries[1][rowIndex] = vector.y;
			entries[2][rowIndex] = vector.z;
			entries[3][rowIndex] = vector.w;
		}

		Vector3D Matrix4D::AffineVector() const
		{
			return Vector3D(entries[3][0], entries[3][1], entries[3][2]);
		}

		Matrix3D Matrix4D::AffineMatrix() const
		{
			return Matrix3D(entries[0][0], entries[1][0], entries[2][0],
							entries[0][1], entries[1][1], entries[2][1], 
							entries[0][2], entries[1][2], entries[2][2]);
		}

		Matrix3D Matrix4D::NormalMatrix() const
		{
			return AffineMatrix().Inverse().Transpose();
		}

		Matrix4D Matrix4D::MakeRotationX(float angle)
		{
			float radians = DegreesToRad(angle);
			float cos = std::cos(radians);
			float sin = std::sin(radians);

			return Matrix4D(1.0f, 0.0f, 0.0f, 0.0f,
							0.0f, cos, -sin, 0.0f,
							0.0f, sin, cos, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f);
		}

		Matrix4D Matrix4D::MakeRotationY(float angle)
		{
			float radians = DegreesToRad(angle);
			float cos = std::cos(radians);
			float sin = std::sin(radians);

			return Matrix4D(cos, 0.0f, sin, 0.0f,
							0.0f, 1.0f, 0.0f, 0.0f,
							-sin, 0.0f, cos, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f);
		}

		Matrix4D Matrix4D::MakeRotationZ(float angle)
		{
			float radians = DegreesToRad(angle);
			float cos = std::cos(radians);
			float sin = std::sin(radians);

			return Matrix4D(cos, -sin, 0.0f, 0.0f,
							sin, cos, 0.0f, 0.0f,
							0.0f, 0.0f, 1.0f, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f);
		}

		Matrix4D Matrix4D::MakeRotaion(float angle, const Vector3D& axis)
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

			return Matrix4D(cos + x * axis.x, axisXAxisY - sin * axis.z, axisXAxisZ + sin * axis.y, 0.0f,
							axisXAxisY + sin * axis.z, cos + y * axis.y, axisYAxisZ - sin * axis.x, 0.0f,
							axisXAxisZ - sin * axis.y, axisYAxisZ + sin * axis.x, cos + z * axis.z, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f);		
		}

		Matrix4D Matrix4D::MakeScale(float uniformScale)
		{
			return Matrix4D(uniformScale, 0.0f, 0.0f, 0.0f,
							0.0f, uniformScale, 0.0f, 0.0f,
							0.0f, 0.0f, uniformScale, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f);
		}

		Matrix4D Matrix4D::MakeScale(float scaleX, float scaleY, float scaleZ)
		{
			return Matrix4D(scaleX, 0.0f, 0.0f, 0.0f,
							0.0f, scaleY, 0.0f, 0.0f,
							0.0f, 0.0f, scaleZ, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f);		
		}

		Matrix4D Matrix4D::MakeScale(const Vector3D& vector)
		{
			return Matrix4D(vector.x, 0.0f, 0.0f, 0.0f,
							0.0f, vector.y, 0.0f, 0.0f,
							0.0f, 0.0f, vector.z, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f);
		}

		Matrix4D Matrix4D::MakeTranslation(float uniformTranslation)
		{
			return Matrix4D(1.0f, 0.0f, 0.0f, uniformTranslation,
							0.0f, 1.0f, 0.0f, uniformTranslation,
							0.0f, 0.0f, 1.0f, uniformTranslation,
							0.0f, 0.0f, 0.0f, 1.0f);	
		}

		Matrix4D Matrix4D::MakeTranslation(float translationX, float translationY, float translationZ)
		{
			return Matrix4D(1.0f, 0.0f, 0.0f, translationX,
							0.0f, 1.0f, 0.0f, translationY,
							0.0f, 0.0f, 1.0f, translationZ,
							0.0f, 0.0f, 0.0f, 1.0f);			
		}

		Matrix4D Matrix4D::MakeTranslation(const Vector3D& vector)
		{
			return Matrix4D(1.0f, 0.0f, 0.0f, vector.x,
							0.0f, 1.0f, 0.0f, vector.y,
							0.0f, 0.0f, 1.0f, vector.z,
							0.0f, 0.0f, 0.0f, 1.0f);	
		}

		Matrix4D Matrix4D::Orthographic(float left, float right, float bottom, float top, float near, float far)
		{
			return Matrix4D(2.0f / (right - left), 0.0f, 0.0f, (left + right) / (left - right),
							0.0f, 2.0f / (top - bottom), 0.0f, (bottom + top) / (bottom - top),
							0.0f, 0.0f, 2.0f / (near - far), (near + far) / (far - near),
							0.0f, 0.0f, 0.0f, 1.0f);
		}

		Matrix4D Matrix4D::Perspective(float fieldOfViewInDegrees, float aspectRatio, float near, float far)
		{
			float c = 1.0f / std::tan(fieldOfViewInDegrees / 2.0f);
			float farMinusNear = far - near;

			return Matrix4D(c / aspectRatio, 0.0f, 0.0f, 0.0f,
							0.0f, c, 0.0f, 0.0f,
							0.0f, 0.0f, -1.0f * (far + near) / (farMinusNear), -2.0f * far * near / farMinusNear,
							0.0f, 0.0f, -1.0f, 0.0f);
		}

		Matrix4D Matrix4D::Identity()
		{
			return Matrix4D(1.0f);
		}

		Matrix4D& Matrix4D::operator=(const Matrix4D& matrix)
		{
			std::memcpy(entries, matrix.entries, sizeof(Matrix4D));
			return *this;
		}

		const float& Matrix4D::operator()(int rowIndex, int columnIndex) const
		{
			return entries[columnIndex][rowIndex];
		}

		float& Matrix4D::operator()(int rowIndex, int columnIndex)
		{
			return entries[columnIndex][rowIndex];
		}

		Matrix4D& Matrix4D::operator*=(const Matrix4D& matrix)
		{
			entries[0][0] = entries[0][0] * matrix.entries[0][0] + entries[1][0] * matrix.entries[0][1] + entries[2][0] * entries[0][2] + entries[3][0] * entries[0][3];
			entries[0][1] = entries[0][0] * matrix.entries[1][0] + entries[1][0] * matrix.entries[1][1] + entries[2][0] * entries[1][2] + entries[3][0] * entries[1][3];
			entries[0][2] = entries[0][0] * matrix.entries[2][0] + entries[1][0] * matrix.entries[2][1] + entries[2][0] * entries[2][2] + entries[3][0] * entries[2][3];
			entries[0][3] = entries[0][0] * matrix.entries[3][0] + entries[1][0] * matrix.entries[3][1] + entries[2][0] * entries[3][2] + entries[3][0] * entries[3][3];

			entries[1][0] = entries[0][1] * matrix.entries[0][0] + entries[1][1] * matrix.entries[0][1] + entries[2][1] * entries[0][2] + entries[3][1] * entries[0][3];
			entries[1][1] = entries[0][1] * matrix.entries[1][0] + entries[1][1] * matrix.entries[1][1] + entries[2][1] * entries[1][2] + entries[3][1] * entries[1][3];
			entries[1][2] = entries[0][1] * matrix.entries[2][0] + entries[1][1] * matrix.entries[2][1] + entries[2][1] * entries[2][2] + entries[3][1] * entries[2][3];
			entries[1][3] = entries[0][1] * matrix.entries[3][0] + entries[1][1] * matrix.entries[3][1] + entries[2][1] * entries[3][2] + entries[3][1] * entries[3][3];

			entries[2][0] = entries[0][2] * matrix.entries[0][0] + entries[1][2] * matrix.entries[0][1] + entries[2][2] * entries[0][2] + entries[3][2] * entries[0][3];
			entries[2][1] = entries[0][2] * matrix.entries[1][0] + entries[1][2] * matrix.entries[1][1] + entries[2][2] * entries[1][2] + entries[3][2] * entries[1][3];
			entries[2][2] = entries[0][2] * matrix.entries[2][0] + entries[1][2] * matrix.entries[2][1] + entries[2][2] * entries[2][2] + entries[3][2] * entries[2][3];
			entries[2][3] = entries[0][2] * matrix.entries[3][0] + entries[1][2] * matrix.entries[3][1] + entries[2][2] * entries[3][2] + entries[3][2] * entries[3][3];

			entries[3][0] = entries[0][3] * matrix.entries[0][0] + entries[1][3] * matrix.entries[0][1] + entries[2][3] * entries[0][2] + entries[3][3] * entries[0][3];
			entries[3][1] = entries[0][3] * matrix.entries[1][0] + entries[1][3] * matrix.entries[1][1] + entries[2][3] * entries[1][2] + entries[3][3] * entries[1][3];
			entries[3][2] = entries[0][3] * matrix.entries[2][0] + entries[1][3] * matrix.entries[2][1] + entries[2][3] * entries[2][2] + entries[3][3] * entries[2][3];
			entries[3][3] = entries[0][3] * matrix.entries[3][0] + entries[1][3] * matrix.entries[3][1] + entries[2][3] * entries[3][2] + entries[3][3] * entries[3][3];

			return *this;
		}

		Vector4D Matrix4D::operator*=(const Vector4D& vector)
		{
			return Vector4D(entries[0][0] * vector.x + entries[1][0] * vector.y + entries[2][0] * vector.z + entries[3][0] * vector.w,
							entries[0][1] * vector.x + entries[1][1] * vector.y + entries[2][1] * vector.z + entries[3][1] * vector.w,
							entries[0][2] * vector.x + entries[1][2] * vector.y + entries[2][2] * vector.z + entries[3][2] * vector.w,
							entries[0][3] * vector.x + entries[1][3] * vector.y + entries[2][3] * vector.z + entries[3][3] * vector.w);
		}

		Matrix4D& Matrix4D::operator*=(float scalar)
		{
			entries[0][0] *= scalar;
			entries[0][1] *= scalar;
			entries[0][2] *= scalar;
			entries[0][3] *= scalar;

			entries[1][0] *= scalar;
			entries[1][1] *= scalar;
			entries[1][2] *= scalar;
			entries[1][3] *= scalar;

			entries[2][0] *= scalar;
			entries[2][1] *= scalar;
			entries[2][2] *= scalar;
			entries[2][3] *= scalar;

			entries[3][0] *= scalar;
			entries[3][1] *= scalar;
			entries[3][2] *= scalar;
			entries[3][3] *= scalar;

			return *this;
		}

		Matrix4D operator*(const Matrix4D& leftMatrix, const Matrix4D& rightMatrix)
		{
			Matrix4D leftMatrixCopy = leftMatrix;
			return leftMatrixCopy *= rightMatrix;
		}

		Vector4D operator*(const Matrix4D& matrix, const Vector4D& vector)
		{
			Matrix4D matrixCopy = matrix;
			return matrixCopy *= vector;
		}

		Matrix4D operator*(const Matrix4D& matrix, float scalar)
		{
			Matrix4D matrixCopy = matrix;
			return matrixCopy *= scalar;
		}

		std::ostream& operator<<(std::ostream& stream, const Matrix4D& matrix)
		{
			stream << "( " << matrix(0, 0) << ", " << matrix(0, 1) << ", " << matrix(0, 2) << ", " << matrix(0, 3) << std::endl;
			stream << "  " << matrix(1, 0) << ", " << matrix(1, 1) << ", " << matrix(1, 2) << ", " << matrix(1, 3) << std::endl;
			stream << "  " << matrix(2, 0) << ", " << matrix(2, 1) << ", " << matrix(2, 2) << ", " << matrix(2, 3) << std::endl;
			stream << "  " << matrix(3, 0) << ", " << matrix(3, 1) << ", " << matrix(3, 2) << ", " << matrix(3, 3) << " )";
			return stream;
		}
	}
}
