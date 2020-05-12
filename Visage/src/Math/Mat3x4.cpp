#include <cstring>

#include "Mat3x4.h"
#include "MathFunctions.h"

namespace Visage
{
	namespace Math
	{
		Mat3x4::Mat3x4()
			: entries{ 0.0f }
		{
		}

		Mat3x4::Mat3x4(const float m00, const float m01, const float m02, const float m03,
					   const float m10, const float m11, const float m12, const float m13, 
					   const float m20, const float m21, const float m22, const float m23)
		{
			entries[0][0] = m00;
			entries[0][1] = m10;
			entries[0][2] = m20;

			entries[1][0] = m01;
			entries[1][1] = m11;
			entries[1][2] = m21;

			entries[2][0] = m02;
			entries[2][1] = m12;
			entries[2][2] = m22;

			entries[3][0] = m03;
			entries[3][1] = m13;
			entries[3][2] = m23;
		}

		Mat3x4::Mat3x4(const Vec4& firstRow, 
					   const Vec4& secondRow, 
					   const Vec4& thirdRow)
		{
			entries[0][0] = firstRow.x;
			entries[1][0] = firstRow.y;
			entries[2][0] = firstRow.z;
			entries[3][0] = firstRow.w;

			entries[0][1] = secondRow.x;
			entries[1][1] = secondRow.y;
			entries[2][1] = secondRow.z;
			entries[3][1] = secondRow.w;

			entries[0][2] = thirdRow.x;
			entries[1][2] = thirdRow.y;
			entries[2][2] = thirdRow.z;
			entries[3][2] = thirdRow.w;
		}

		Mat3x4::Mat3x4(const float diagonal)
			: entries{ 0.0f }
		{
			entries[0][0] = diagonal;
			entries[1][1] = diagonal;
			entries[2][2] = diagonal;
		}

		Mat3x4::Mat3x4(const Mat3x4& matrix)
		{
			std::memcpy(entries, matrix.entries, sizeof(Mat3x4));
		}

		Mat3x4 Mat3x4::Inverted() const
		{
			const Vec3 a = reinterpret_cast<const Vec3&>(entries[0]);
			const Vec3 b = reinterpret_cast<const Vec3&>(entries[1]);
			const Vec3 c = reinterpret_cast<const Vec3&>(entries[2]);
			const Vec3 d = reinterpret_cast<const Vec3&>(entries[3]);

			Vec3 s = Vec3::Cross(a, b);
			Vec3 t = Vec3::Cross(c, d);

			float inverseDet = 1.0f / Vec3::Dot(s, c);
			s *= inverseDet;
			t *= inverseDet;
			Vec3 v = c * inverseDet;

			Vec3 firstRow = Vec3::Cross(b, v);
			Vec3 secondRow = Vec3::Cross(v, a);


			return Mat3x4(firstRow.x, firstRow.y, firstRow.z, -Vec3::Dot(b, t),
						  secondRow.x, secondRow.y, secondRow.z, -Vec3::Dot(a, t),
						  s.x, s.y, s.z, -Vec3::Dot(d, s));
		}

		Mat3x4& Mat3x4::Invert()
		{
			const Vec3 a = reinterpret_cast<const Vec3&>(entries[0]);
			const Vec3 b = reinterpret_cast<const Vec3&>(entries[1]);
			const Vec3 c = reinterpret_cast<const Vec3&>(entries[2]);
			const Vec3 d = reinterpret_cast<const Vec3&>(entries[3]);

			Vec3 s = Vec3::Cross(a, b);
			Vec3 t = Vec3::Cross(c, d);

			float inverseDet = 1.0f / Vec3::Dot(s, c);
			s *= inverseDet;
			t *= inverseDet;
			Vec3 v = c * inverseDet;

			Vec3 firstRow = Vec3::Cross(b, v);
			Vec3 secondRow = Vec3::Cross(v, a);

			entries[0][0] = firstRow.x;
			entries[1][0] = firstRow.y;
			entries[2][0] = firstRow.z;
			entries[3][0] = -Vec3::Dot(b, t);

			entries[0][1] = secondRow.x;
			entries[1][1] = secondRow.y;
			entries[2][1] = secondRow.z;
			entries[3][1] = -Vec3::Dot(a, t);

			entries[0][2] = s.x;
			entries[1][2] = s.y;
			entries[2][2] = s.z;
			entries[3][2] = -Vec3::Dot(d, s);

			return *this;
		}

		Mat4 Mat3x4::TransposedMat4() const
		{
			return Mat4(entries[0][0], entries[0][1], entries[0][2], 0.0f,
						entries[1][0], entries[1][1], entries[1][2], 0.0f,
						entries[2][0], entries[2][1], entries[2][2], 0.0f,
						entries[3][0], entries[3][1], entries[3][2], 1.0f);
		}

		float Mat3x4::Determinant() const
		{
			const Vec3 a = reinterpret_cast<const Vec3&>(entries[0]);
			const Vec3 b = reinterpret_cast<const Vec3&>(entries[1]);
			const Vec3 c = reinterpret_cast<const Vec3&>(entries[2]);
			const Vec3 d = reinterpret_cast<const Vec3&>(entries[3]);

			Vec3 s = Vec3::Cross(a, b);
			Vec3 t = Vec3::Cross(c, d);

			return Vec3::Dot(s, c);
		}

		Vec3 Mat3x4::GetColumn(const int columnIndex) const
		{
			return Vec3(entries[columnIndex][0],
						entries[columnIndex][1],
						entries[columnIndex][2]);
		}

		void Mat3x4::SetColumn(const int columnIndex, const Vec3& vector)
		{
			entries[columnIndex][0] = vector.x;
			entries[columnIndex][1] = vector.y;
			entries[columnIndex][2] = vector.z;
		}

		Vec4 Mat3x4::GetRow(const int rowIndex) const
		{
			return Vec4(entries[0][rowIndex],
						entries[1][rowIndex],
						entries[2][rowIndex],
						entries[3][rowIndex]);
		}

		void Mat3x4::SetRow(const int rowIndex, const Vec4& vector)
		{
			entries[0][rowIndex] = vector.x;
			entries[1][rowIndex] = vector.y;
			entries[2][rowIndex] = vector.z;
			entries[3][rowIndex] = vector.w;
		}

		Vec3 Mat3x4::GetTranslation() const
		{
			return Vec3(entries[3][0],
						entries[3][1],
						entries[3][2]);
		}

		void Mat3x4::SetTranslation(const Vec3& translation)
		{
			entries[3][0] = translation.x;
			entries[3][1] = translation.y;
			entries[3][2] = translation.z;
		}

		Mat3 Mat3x4::AffineMatrix() const
		{
			return Mat3(entries[0][0], entries[1][0], entries[2][0],
						entries[0][1], entries[1][1], entries[2][1],
						entries[0][2], entries[1][2], entries[2][2]);
		}

		Mat3 Mat3x4::NormalMatrix() const
		{
			return AffineMatrix().Inverted().Transposed();
		}

		Mat4 Mat3x4::ToMat4() const
		{
			return Mat4();
		}

		Mat3x4 Mat3x4::MakeRotationX(const float angleInDegrees)
		{
			float radians = DegreesToRad(angleInDegrees);
			float cos = std::cos(radians);
			float sin = std::sin(radians);

			return Mat3x4(1.0f, 0.0f, 0.0f, 0.0f,
						  0.0f, cos, -sin, 0.0f,
						  0.0f, sin, cos, 0.0f);
		}

		Mat3x4 Mat3x4::MakeRotationY(const float angleInDegrees)
		{
			float radians = DegreesToRad(angleInDegrees);
			float cos = std::cos(radians);
			float sin = std::sin(radians);

			return Mat3x4(cos, 0.0f, sin, 0.0f,
						  0.0f, 1.0f, 0.0f, 0.0f,
						  -sin, 0.0f, cos, 0.0f);
		}

		Mat3x4 Mat3x4::MakeRotationZ(const float angleInDegrees)
		{
			float radians = DegreesToRad(angleInDegrees);
			float cos = std::cos(radians);
			float sin = std::sin(radians);

			return Mat3x4(cos, -sin, 0.0f, 0.0f,
						  sin, cos, 0.0f, 0.0f,
						  0.0f, 0.0f, 1.0f, 0.0f);
		}

		Mat3x4 Mat3x4::MakeRotation(const Vec3& axis, const float angleInDegrees)
		{
			float radians = DegreesToRad(angleInDegrees);
			float cos = std::cos(radians);
			float sin = std::sin(radians);
			float oneMinsCos = 1.0f - cos;

			float x = axis.x * oneMinsCos;
			float y = axis.y * oneMinsCos;
			float z = axis.z * oneMinsCos;
			float axisXAxisY = x * axis.y;
			float axisXAxisZ = x * axis.z;
			float axisYAxisZ = y * axis.z;

			return Mat3x4(cos + x * axis.x, axisXAxisY - sin * axis.z, axisXAxisZ + sin * axis.y, 0.0f,
						  axisXAxisY + sin * axis.z, cos + y * axis.y, axisYAxisZ - sin * axis.x, 0.0f,
						  axisXAxisZ - sin * axis.y, axisYAxisZ + sin * axis.x, cos + z * axis.z, 0.0f);
		}

		Mat3x4 Mat3x4::MakeScale(const float uniformScale)
		{
			return Mat3x4(uniformScale, 0.0f, 0.0f, 0.0f,
						  0.0f, uniformScale, 0.0f, 0.0f,
						  0.0f, 0.0f, uniformScale, 0.0f);
		}

		Mat3x4 Mat3x4::MakeScale(const float scaleX, const float scaleY, const float scaleZ)
		{
			return Mat3x4(scaleX, 0.0f, 0.0f, 0.0f,
						  0.0f, scaleY, 0.0f, 0.0f,
						  0.0f, 0.0f, scaleZ, 0.0f);
		}

		Mat3x4 Mat3x4::MakeScale(const Vec3& vector)
		{
			return Mat3x4(vector.x, 0.0f, 0.0f, 0.0f,
						  0.0f, vector.y, 0.0f, 0.0f,
						  0.0f, 0.0f, vector.z, 0.0f);
		}

		Mat3x4 Mat3x4::MakeTranslation(const float uniformTranslation)
		{
			return Mat3x4(1.0f, 0.0f, 0.0f, uniformTranslation,
						  0.0f, 1.0f, 0.0f, uniformTranslation,
						  0.0f, 0.0f, 1.0f, uniformTranslation);
		}

		Mat3x4 Mat3x4::MakeTranslation(const float translationX, const float translationY, const float translationZ)
		{
			return Mat3x4(1.0f, 0.0f, 0.0f, translationX,
						  0.0f, 1.0f, 0.0f, translationY,
						  0.0f, 0.0f, 1.0f, translationZ);
		}

		Mat3x4 Mat3x4::MakeTranslation(const Vec3& vector)
		{
			return Mat3x4(1.0f, 0.0f, 0.0f, vector.x,
						  0.0f, 1.0f, 0.0f, vector.y,
						  0.0f, 0.0f, 1.0f, vector.z);
		}

		Mat3x4 Mat3x4::LookAt(const Vec3& cameraPosition, const Vec3& targetPosition, const Vec3& up)
		{
			Vec3 forwardAxis = (cameraPosition - targetPosition).Normalize();
			Vec3 rightAxis = Vec3::Cross(up, forwardAxis).Normalize();
			Vec3 upAxis = Vec3::Cross(forwardAxis, rightAxis).Normalize();

			return Mat3x4(rightAxis.x, rightAxis.y, rightAxis.z, -Vec3::Dot(rightAxis, cameraPosition),
						  upAxis.x, upAxis.y, upAxis.z, -Vec3::Dot(upAxis, cameraPosition),
						  forwardAxis.x, forwardAxis.y, forwardAxis.z, -Vec3::Dot(forwardAxis, cameraPosition));
		}

		Mat3x4 Mat3x4::Orthographic(const float left, const float right, const float bottom, const float top, const float near, const float far)
		{
			return Mat3x4(2.0f / (right - left), 0.0f, 0.0f, (left + right) / (left - right),
						  0.0f, 2.0f / (top - bottom), 0.0f, (bottom + top) / (bottom - top),
						  0.0f, 0.0f, 2.0f / (near - far), (near + far) / (far - near));
		}

		Mat3x4 Mat3x4::Identity()
		{
			return Mat3x4(1.0);
		}

		Mat3x4& Mat3x4::operator=(const Mat3x4& matrix)
		{
			std::memcpy(entries, matrix.entries, sizeof(Mat3x4));
			return *this;
		}

		Mat3x4& Mat3x4::operator*=(const Mat3x4& matrix)
		{
			entries[0][0] = entries[0][0] * matrix.entries[0][0] + entries[1][0] * matrix.entries[0][1] + entries[2][0] * matrix.entries[0][2];
			entries[1][0] = entries[0][0] * matrix.entries[1][0] + entries[1][0] * matrix.entries[1][1] + entries[2][0] * matrix.entries[1][2];
			entries[2][0] = entries[0][0] * matrix.entries[2][0] + entries[1][0] * matrix.entries[2][1] + entries[2][0] * matrix.entries[2][2];
			entries[3][0] = entries[0][0] * matrix.entries[3][0] + entries[1][0] * matrix.entries[3][1] + entries[2][0] * matrix.entries[3][2] + entries[3][0];

			entries[0][1] = entries[0][1] * matrix.entries[0][0] + entries[1][1] * matrix.entries[0][1] + entries[2][1] * matrix.entries[0][2];
			entries[1][1] = entries[0][1] * matrix.entries[1][0] + entries[1][1] * matrix.entries[1][1] + entries[2][1] * matrix.entries[1][2];
			entries[2][1] = entries[0][1] * matrix.entries[2][0] + entries[1][1] * matrix.entries[2][1] + entries[2][1] * matrix.entries[2][2];
			entries[3][1] = entries[0][1] * matrix.entries[3][0] + entries[1][1] * matrix.entries[3][1] + entries[2][1] * matrix.entries[3][2] + entries[3][1];

			entries[0][2] = entries[0][2] * matrix.entries[0][0] + entries[1][2] * matrix.entries[0][1] + entries[2][2] * matrix.entries[0][2];
			entries[1][2] = entries[0][2] * matrix.entries[1][0] + entries[1][2] * matrix.entries[1][1] + entries[2][2] * matrix.entries[1][2];
			entries[2][2] = entries[0][2] * matrix.entries[2][0] + entries[1][2] * matrix.entries[2][1] + entries[2][2] * matrix.entries[2][2];
			entries[3][2] = entries[0][2] * matrix.entries[3][0] + entries[1][2] * matrix.entries[3][1] + entries[2][2] * matrix.entries[3][2] + entries[3][2];

			return *this;
		}

		Mat3x4& Mat3x4::operator*=(const float scalar)
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

			entries[3][0] *= scalar;
			entries[3][1] *= scalar;
			entries[3][2] *= scalar;

			return *this;
		}

		Mat3x4 operator*(const Mat3x4& leftMatrix, const Mat3x4& rightMatrix)
		{
			Mat3x4 leftMatrixCopy = leftMatrix;
			return leftMatrixCopy *= rightMatrix;
		}

		Mat4 operator*(const Mat3x4& leftMatrix, const Mat4& rightMatrix)
		{
			Mat4 result;

			result(0, 0) = leftMatrix(0, 0) * rightMatrix(0, 0) + leftMatrix(0, 1) * rightMatrix(1, 0) + leftMatrix(0, 2) * rightMatrix(2, 0) + leftMatrix(0, 3) * rightMatrix(3, 0);
			result(0, 1) = leftMatrix(0, 0) * rightMatrix(0, 1) + leftMatrix(0, 1) * rightMatrix(1, 1) + leftMatrix(0, 2) * rightMatrix(2, 1) + leftMatrix(0, 3) * rightMatrix(3, 0);
			result(0, 2) = leftMatrix(0, 0) * rightMatrix(0, 2) + leftMatrix(0, 1) * rightMatrix(1, 2) + leftMatrix(0, 2) * rightMatrix(2, 2) + leftMatrix(0, 3) * rightMatrix(3, 0);
			result(0, 3) = leftMatrix(0, 0) * rightMatrix(0, 3) + leftMatrix(0, 1) * rightMatrix(1, 3) + leftMatrix(0, 2) * rightMatrix(2, 3) + leftMatrix(0, 3) * rightMatrix(3, 0);

			result(1, 0) = leftMatrix(1, 0) * rightMatrix(0, 0) + leftMatrix(1, 1) * rightMatrix(1, 0) + leftMatrix(1, 2) * rightMatrix(2, 0) + leftMatrix(1, 3) * rightMatrix(3, 0);
			result(1, 1) = leftMatrix(1, 0) * rightMatrix(0, 1) + leftMatrix(1, 1) * rightMatrix(1, 1) + leftMatrix(1, 2) * rightMatrix(2, 1) + leftMatrix(1, 3) * rightMatrix(3, 0);
			result(1, 2) = leftMatrix(1, 0) * rightMatrix(0, 2) + leftMatrix(1, 1) * rightMatrix(1, 2) + leftMatrix(1, 2) * rightMatrix(2, 2) + leftMatrix(1, 3) * rightMatrix(3, 0);
			result(1, 3) = leftMatrix(1, 0) * rightMatrix(0, 3) + leftMatrix(1, 1) * rightMatrix(1, 3) + leftMatrix(1, 2) * rightMatrix(2, 3) + leftMatrix(1, 3) * rightMatrix(3, 0);

			result(2, 0) = leftMatrix(2, 0) * rightMatrix(0, 0) + leftMatrix(2, 1) * rightMatrix(1, 0) + leftMatrix(2, 2) * rightMatrix(2, 0) + leftMatrix(2, 3) * rightMatrix(3, 0);
			result(2, 1) = leftMatrix(2, 0) * rightMatrix(0, 1) + leftMatrix(2, 1) * rightMatrix(1, 1) + leftMatrix(2, 2) * rightMatrix(2, 1) + leftMatrix(2, 3) * rightMatrix(3, 0);
			result(2, 2) = leftMatrix(2, 0) * rightMatrix(0, 2) + leftMatrix(2, 1) * rightMatrix(1, 2) + leftMatrix(2, 2) * rightMatrix(2, 2) + leftMatrix(2, 3) * rightMatrix(3, 0);
			result(2, 3) = leftMatrix(2, 0) * rightMatrix(0, 3) + leftMatrix(2, 1) * rightMatrix(1, 3) + leftMatrix(2, 2) * rightMatrix(2, 3) + leftMatrix(2, 3) * rightMatrix(3, 0);

			result(3, 0) = rightMatrix(3, 0);
			result(3, 1) = rightMatrix(3, 1);
			result(3, 2) = rightMatrix(3, 2);
			result(3, 3) = rightMatrix(3, 3);

			return result;
		}

		Mat4 operator*(const Mat4& leftMatrix, const Mat3x4& rightMatrix)
		{
			return rightMatrix * leftMatrix;
		}

		Vec4 operator*(const Mat3x4& matrix, const Vec4& vector)
		{
			return Vec4(matrix(0, 0) * vector.x + matrix(1, 0) * vector.y + matrix(2, 0) * vector.z + matrix(3, 0) * vector.w,
						matrix(0, 1) * vector.x + matrix(1, 1) * vector.y + matrix(2, 1) * vector.z + matrix(3, 1) * vector.w,
						matrix(0, 2) * vector.x + matrix(1, 2) * vector.y + matrix(2, 2) * vector.z + matrix(3, 2) * vector.w,
						vector.w);
		}

		Vec3 operator*(const Mat3x4& matrix, const Vec3& vector)
		{
			return Vec3(matrix(0, 0) * vector.x + matrix(1, 0) * vector.y + matrix(2, 0) * vector.z,
						matrix(0, 1) * vector.x + matrix(1, 1) * vector.y + matrix(2, 1) * vector.z,
						matrix(0, 2) * vector.x + matrix(1, 2) * vector.y + matrix(2, 2) * vector.z);
		}

		Mat3x4 operator*(const Mat3x4& matrix, const float scalar)
		{
			Mat3x4 matrixCopy = matrix;
			return matrixCopy *= scalar;
		}

		std::ostream& operator<<(std::ostream& stream, const Mat3x4& matrix)
		{
			stream << "( " << matrix(0, 0) << ", " << matrix(0, 1) << ", " << matrix(0, 2) << ", " << matrix(0, 3) << std::endl;
			stream << "  " << matrix(1, 0) << ", " << matrix(1, 1) << ", " << matrix(1, 2) << ", " << matrix(1, 3) << std::endl;
			stream << "  " << matrix(2, 0) << ", " << matrix(2, 1) << ", " << matrix(2, 2) << ", " << matrix(2, 3) << " )";
			return stream;
		}
	}
}