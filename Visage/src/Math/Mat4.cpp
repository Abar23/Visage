#include <cstring>
#include <cmath>
#include "Mat4.h"
#include "MathFunctions.h"

namespace Visage
{
	namespace Math
	{
		Visage::Math::Mat4::Mat4()
			: entries{ 0.0f } 
		{
		}

		Mat4::Mat4(float m00, float m01, float m02, float m03, 
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

		Mat4::Mat4(const Vec4& firstRow, 
				   const Vec4& secondRow, 
				   const Vec4& thirdRow, 
				   const Vec4& fourthRow)
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

			entries[0][3] = fourthRow.x;
			entries[1][3] = fourthRow.y;
			entries[2][3] = fourthRow.z;
			entries[3][3] = fourthRow.w;
		}

		Mat4::Mat4(float diagonal)
			: entries{ 0.0f }
		{
			entries[0][0] = diagonal;
			entries[1][1] = diagonal;
			entries[2][2] = diagonal;
			entries[3][3] = diagonal;
		}

		Mat4::Mat4(const Mat4& matrix)
		{
			std::memcpy(entries, matrix.entries, sizeof(Mat4));
		}

		Mat4 Mat4::Inverted() const
		{
			const Vec3 a = reinterpret_cast<const Vec3&>(entries[0]);
			const Vec3 b = reinterpret_cast<const Vec3&>(entries[1]);
			const Vec3 c = reinterpret_cast<const Vec3&>(entries[2]);
			const Vec3 d = reinterpret_cast<const Vec3&>(entries[3]);

			float x = entries[0][3];
			float y = entries[1][3];
			float z = entries[2][3];
			float w = entries[3][3];

			Vec3 s = Vec3::Cross(a, b);
			Vec3 t = Vec3::Cross(c, d);
			Vec3 u = a * y - b * x;
			Vec3 v = c * w - d * z;

			float inverseDet = 1.0f / Vec3::Dot(s, v) - Vec3::Dot(t, u);
			s *= inverseDet;
			t *= inverseDet;
			u *= inverseDet;
			v *= inverseDet;

			Vec3 firstRow = Vec3::Cross(b, v) + t * y;
			Vec3 secondRow = Vec3::Cross(v, a) - t * x;
			Vec3 thirdRow = Vec3::Cross(d, u) + s * w;
			Vec3 fourthRow = Vec3::Cross(u, c) - s * z;

			return Mat4(firstRow.x, firstRow.y, firstRow.z, -Vec3::Dot(b, t),
						secondRow.x, secondRow.y, secondRow.z, Vec3::Dot(a, t),
						thirdRow.x, thirdRow.y, thirdRow.z, -Vec3::Dot(d, s),
						fourthRow.x, fourthRow.y, fourthRow.z, Vec3::Dot(c, s));
		}

		Mat4& Mat4::Invert()
		{
			const Vec3 a = reinterpret_cast<const Vec3&>(entries[0]);
			const Vec3 b = reinterpret_cast<const Vec3&>(entries[1]);
			const Vec3 c = reinterpret_cast<const Vec3&>(entries[2]);
			const Vec3 d = reinterpret_cast<const Vec3&>(entries[3]);

			float x = entries[0][3];
			float y = entries[1][3];
			float z = entries[2][3];
			float w = entries[3][3];

			Vec3 s = Vec3::Cross(a, b);
			Vec3 t = Vec3::Cross(c, d);
			Vec3 u = a * y - b * x;
			Vec3 v = c * w - d * z;

			float inverseDet = 1.0f / Vec3::Dot(s, v) - Vec3::Dot(t, u);
			s *= inverseDet;
			t *= inverseDet;
			u *= inverseDet;
			v *= inverseDet;

			Vec3 firstRow = Vec3::Cross(b, v) + t * y;
			Vec3 secondRow = Vec3::Cross(v, a) - t * x;
			Vec3 thirdRow = Vec3::Cross(d, u) + s * w;
			Vec3 fourthRow = Vec3::Cross(u, c) - s * z;

			entries[0][0] = firstRow.x;
			entries[1][0] = firstRow.y;
			entries[2][0] = firstRow.z;
			entries[3][0] = -Vec3::Dot(b, t);

			entries[0][1] = secondRow.x;
			entries[1][1] = secondRow.y;
			entries[2][1] = secondRow.z;
			entries[3][1] = -Vec3::Dot(a, t);

			entries[0][2] = thirdRow.x;
			entries[1][2] = thirdRow.y;
			entries[2][2] = thirdRow.z;
			entries[3][2] = -Vec3::Dot(d, s);

			entries[0][3] = fourthRow.x;
			entries[1][3] = fourthRow.y;
			entries[2][3] = fourthRow.z;
			entries[3][3] = -Vec3::Dot(c, s);

			return *this;
		}

		Mat4 Mat4::Transposed() const
		{
			return Mat4(entries[0][0], entries[0][1], entries[0][2], entries[0][3],
						entries[1][0], entries[1][1], entries[1][2], entries[1][3],
						entries[2][0], entries[2][1], entries[2][2], entries[2][3],
						entries[3][0], entries[3][1], entries[3][2], entries[3][3]);
		}

		Mat4& Mat4::Transpose()
		{
			Mat4 temp = *this;

			entries[0][1] = temp.entries[1][0];
			entries[0][2] = temp.entries[2][0];
			entries[0][3] = temp.entries[3][0];

			entries[1][0] = temp.entries[0][1];
			entries[1][2] = temp.entries[2][1];
			entries[1][3] = temp.entries[3][1];

			entries[2][0] = temp.entries[0][2];
			entries[2][1] = temp.entries[1][2];
			entries[2][3] = temp.entries[3][2];

			entries[3][0] = temp.entries[0][3];
			entries[3][1] = temp.entries[1][3];
			entries[3][2] = temp.entries[2][3];

			return *this;
		}

		float Mat4::Determinant() const
		{
			const Vec3 a = reinterpret_cast<const Vec3&>(entries[0]);
			const Vec3 b = reinterpret_cast<const Vec3&>(entries[1]);
			const Vec3 c = reinterpret_cast<const Vec3&>(entries[2]);
			const Vec3 d = reinterpret_cast<const Vec3&>(entries[3]);

			Vec3 s = Vec3::Cross(a, b);
			Vec3 t = Vec3::Cross(c, d);
			Vec3 u = a * entries[1][3] - b * entries[0][3];
			Vec3 v = c * entries[3][3] - d * entries[2][3];

			return Vec3::Dot(s, v) - Vec3::Dot(t, u);
		}

		Vec4 Mat4::GetColumn(int columnIndex) const
		{
			return Vec4(entries[columnIndex][0], 
						entries[columnIndex][1], 
						entries[columnIndex][2],
						entries[columnIndex][3]);
		}

		void Mat4::SetColumn(int columnIndex, const Vec4& vector)
		{
			entries[columnIndex][0] = vector.x;
			entries[columnIndex][1] = vector.y;
			entries[columnIndex][2] = vector.z;
			entries[columnIndex][3] = vector.w;
		}

		Vec4 Mat4::GetRow(int rowIndex) const
		{
			return Vec4(entries[0][rowIndex], 
						entries[1][rowIndex], 
						entries[2][rowIndex], 
						entries[3][rowIndex]);
		}

		void Mat4::SetRow(int rowIndex, const Vec4& vector)
		{
			entries[0][rowIndex] = vector.x;
			entries[1][rowIndex] = vector.y;
			entries[2][rowIndex] = vector.z;
			entries[3][rowIndex] = vector.w;
		}

		Vec3 Mat4::GetTranslation() const
		{
			return Vec3(entries[3][0], 
						entries[3][1], 
						entries[3][2]);
		}

		void Mat4::SetTranslation(const Vec3& translation)
		{
			entries[3][0] = translation.x;
			entries[3][1] = translation.y;
			entries[3][2] = translation.z;
		}

		Mat3 Mat4::AffineMatrix() const
		{
			return Mat3(entries[0][0], entries[1][0], entries[2][0],
						entries[0][1], entries[1][1], entries[2][1], 
						entries[0][2], entries[1][2], entries[2][2]);
		}

		Mat3 Mat4::NormalMatrix() const
		{
			return AffineMatrix().Inverted().Transposed();
		}

		Mat4 Mat4::MakeRotationX(float angle)
		{
			float radians = DegreesToRad(angle);
			float cos = std::cos(radians);
			float sin = std::sin(radians);

			return Mat4(1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, cos, -sin, 0.0f,
						0.0f, sin, cos, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);
		}

		Mat4 Mat4::MakeRotationY(float angle)
		{
			float radians = DegreesToRad(angle);
			float cos = std::cos(radians);
			float sin = std::sin(radians);

			return Mat4(cos, 0.0f, sin, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						-sin, 0.0f, cos, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);
		}

		Mat4 Mat4::MakeRotationZ(float angle)
		{
			float radians = DegreesToRad(angle);
			float cos = std::cos(radians);
			float sin = std::sin(radians);

			return Mat4(cos, -sin, 0.0f, 0.0f,
						sin, cos, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);
		}

		Mat4 Mat4::MakeRotation(float angle, const Vec3& axis)
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

			return Mat4(cos + x * axis.x, axisXAxisY - sin * axis.z, axisXAxisZ + sin * axis.y, 0.0f,
						axisXAxisY + sin * axis.z, cos + y * axis.y, axisYAxisZ - sin * axis.x, 0.0f,
						axisXAxisZ - sin * axis.y, axisYAxisZ + sin * axis.x, cos + z * axis.z, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);
		}

		Mat4 Mat4::MakeScale(float uniformScale)
		{
			return Mat4(uniformScale, 0.0f, 0.0f, 0.0f,
						0.0f, uniformScale, 0.0f, 0.0f,
						0.0f, 0.0f, uniformScale, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);
		}

		Mat4 Mat4::MakeScale(float scaleX, float scaleY, float scaleZ)
		{
			return Mat4(scaleX, 0.0f, 0.0f, 0.0f,
						0.0f, scaleY, 0.0f, 0.0f,
						0.0f, 0.0f, scaleZ, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);		
		}

		Mat4 Mat4::MakeScale(const Vec3& vector)
		{
			return Mat4(vector.x, 0.0f, 0.0f, 0.0f,
						0.0f, vector.y, 0.0f, 0.0f,
						0.0f, 0.0f, vector.z, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);
		}

		Mat4 Mat4::MakeTranslation(float uniformTranslation)
		{
			return Mat4(1.0f, 0.0f, 0.0f, uniformTranslation,
						0.0f, 1.0f, 0.0f, uniformTranslation,
						0.0f, 0.0f, 1.0f, uniformTranslation,
						0.0f, 0.0f, 0.0f, 1.0f);	
		}

		Mat4 Mat4::MakeTranslation(float translationX, float translationY, float translationZ)
		{
			return Mat4(1.0f, 0.0f, 0.0f, translationX,
						0.0f, 1.0f, 0.0f, translationY,
						0.0f, 0.0f, 1.0f, translationZ,
						0.0f, 0.0f, 0.0f, 1.0f);			
		}

		Mat4 Mat4::MakeTranslation(const Vec3& vector)
		{
			return Mat4(1.0f, 0.0f, 0.0f, vector.x,
						0.0f, 1.0f, 0.0f, vector.y,
						0.0f, 0.0f, 1.0f, vector.z,
						0.0f, 0.0f, 0.0f, 1.0f);	
		}

		Mat4 Mat4::LookAt(const Vec3& cameraPosition, const Vec3& targetPosition, const Vec3& up)
		{
			Vec3 forwardAxis = (cameraPosition - targetPosition).Normalize();
			Vec3 rightAxis = Vec3::Cross(up, forwardAxis).Normalize();
			Vec3 upAxis = Vec3::Cross(forwardAxis, rightAxis).Normalize();
			
			return Mat4(rightAxis.x, rightAxis.y, rightAxis.z, -Vec3::Dot(rightAxis, cameraPosition),
						upAxis.x, upAxis.y, upAxis.z, -Vec3::Dot(upAxis, cameraPosition),
						forwardAxis.x, forwardAxis.y, forwardAxis.z, -Vec3::Dot(forwardAxis, cameraPosition),
						0.0f, 0.0f, 0.0f, 1.0f);
		}

		Mat4 Mat4::Orthographic(float left, float right, float bottom, float top, float near, float far)
		{
			return Mat4(2.0f / (right - left), 0.0f, 0.0f, (left + right) / (left - right),
						0.0f, 2.0f / (top - bottom), 0.0f, (bottom + top) / (bottom - top),
						0.0f, 0.0f, 2.0f / (near - far), (near + far) / (far - near),
						0.0f, 0.0f, 0.0f, 1.0f);
		}

		Mat4 Mat4::Perspective(float fieldOfViewInDegrees, float aspectRatio, float near, float far)
		{
			float c = 1.0f / std::tan(fieldOfViewInDegrees / 2.0f);
			float farMinusNear = far - near;

			return Mat4(c / aspectRatio, 0.0f, 0.0f, 0.0f,
						0.0f, c, 0.0f, 0.0f,
						0.0f, 0.0f, -1.0f * (far + near) / (farMinusNear), -2.0f * far * near / farMinusNear,
						0.0f, 0.0f, -1.0f, 0.0f);
		}

		Mat4 Mat4::Identity()
		{
			return Mat4(1.0f);
		}

		Mat4& Mat4::operator=(const Mat4& matrix)
		{
			std::memcpy(entries, matrix.entries, sizeof(Mat4));
			return *this;
		}

		Mat4& Mat4::operator*=(const Mat4& matrix)
		{
			entries[0][0] = entries[0][0] * matrix.entries[0][0] + entries[1][0] * matrix.entries[0][1] + entries[2][0] * matrix.entries[0][2] + entries[3][0] * matrix.entries[0][3];
			entries[1][0] = entries[0][0] * matrix.entries[1][0] + entries[1][0] * matrix.entries[1][1] + entries[2][0] * matrix.entries[1][2] + entries[3][0] * matrix.entries[1][3];
			entries[2][0] = entries[0][0] * matrix.entries[2][0] + entries[1][0] * matrix.entries[2][1] + entries[2][0] * matrix.entries[2][2] + entries[3][0] * matrix.entries[2][3];
			entries[3][0] = entries[0][0] * matrix.entries[3][0] + entries[1][0] * matrix.entries[3][1] + entries[2][0] * matrix.entries[3][2] + entries[3][0] * matrix.entries[3][3];

			entries[0][1] = entries[0][1] * matrix.entries[0][0] + entries[1][1] * matrix.entries[0][1] + entries[2][1] * matrix.entries[0][2] + entries[3][1] * matrix.entries[0][3];
			entries[1][1] = entries[0][1] * matrix.entries[1][0] + entries[1][1] * matrix.entries[1][1] + entries[2][1] * matrix.entries[1][2] + entries[3][1] * matrix.entries[1][3];
			entries[2][1] = entries[0][1] * matrix.entries[2][0] + entries[1][1] * matrix.entries[2][1] + entries[2][1] * matrix.entries[2][2] + entries[3][1] * matrix.entries[2][3];
			entries[3][1] = entries[0][1] * matrix.entries[3][0] + entries[1][1] * matrix.entries[3][1] + entries[2][1] * matrix.entries[3][2] + entries[3][1] * matrix.entries[3][3];

			entries[0][2] = entries[0][2] * matrix.entries[0][0] + entries[1][2] * matrix.entries[0][1] + entries[2][2] * matrix.entries[0][2] + entries[3][2] * matrix.entries[0][3];
			entries[1][2] = entries[0][2] * matrix.entries[1][0] + entries[1][2] * matrix.entries[1][1] + entries[2][2] * matrix.entries[1][2] + entries[3][2] * matrix.entries[1][3];
			entries[2][2] = entries[0][2] * matrix.entries[2][0] + entries[1][2] * matrix.entries[2][1] + entries[2][2] * matrix.entries[2][2] + entries[3][2] * matrix.entries[2][3];
			entries[3][2] = entries[0][2] * matrix.entries[3][0] + entries[1][2] * matrix.entries[3][1] + entries[2][2] * matrix.entries[3][2] + entries[3][2] * matrix.entries[3][3];

			entries[0][3] = entries[0][3] * matrix.entries[0][0] + entries[1][3] * matrix.entries[0][1] + entries[2][3] * matrix.entries[0][2] + entries[3][3] * matrix.entries[0][3];
			entries[1][3] = entries[0][3] * matrix.entries[1][0] + entries[1][3] * matrix.entries[1][1] + entries[2][3] * matrix.entries[1][2] + entries[3][3] * matrix.entries[1][3];
			entries[2][3] = entries[0][3] * matrix.entries[2][0] + entries[1][3] * matrix.entries[2][1] + entries[2][3] * matrix.entries[2][2] + entries[3][3] * matrix.entries[2][3];
			entries[3][3] = entries[0][3] * matrix.entries[3][0] + entries[1][3] * matrix.entries[3][1] + entries[2][3] * matrix.entries[3][2] + entries[3][3] * matrix.entries[3][3];

			return *this;
		}

		Mat4& Mat4::operator*=(float scalar)
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

		Mat4 operator*(const Mat4& leftMatrix, const Mat4& rightMatrix)
		{
			Mat4 leftMatrixCopy = leftMatrix;
			return leftMatrixCopy *= rightMatrix;
		}

		Vec4 operator*(const Mat4& matrix, const Vec4& vector)
		{
			return Vec4(matrix(0, 0) * vector.x + matrix(1, 0) * vector.y + matrix(2, 0) * vector.z + matrix(3, 0) * vector.w,
						matrix(0, 1) * vector.x + matrix(1, 1) * vector.y + matrix(2, 1) * vector.z + matrix(3, 1) * vector.w,
						matrix(0, 2) * vector.x + matrix(1, 2) * vector.y + matrix(2, 2) * vector.z + matrix(3, 2) * vector.w,
						matrix(0, 3) * vector.x + matrix(1, 3) * vector.y + matrix(2, 3) * vector.z + matrix(3, 3) * vector.w);
		}

		Mat4 operator*(const Mat4& matrix, float scalar)
		{
			Mat4 matrixCopy = matrix;
			return matrixCopy *= scalar;
		}

		std::ostream& operator<<(std::ostream& stream, const Mat4& matrix)
		{
			stream << "( " << matrix(0, 0) << ", " << matrix(0, 1) << ", " << matrix(0, 2) << ", " << matrix(0, 3) << std::endl;
			stream << "  " << matrix(1, 0) << ", " << matrix(1, 1) << ", " << matrix(1, 2) << ", " << matrix(1, 3) << std::endl;
			stream << "  " << matrix(2, 0) << ", " << matrix(2, 1) << ", " << matrix(2, 2) << ", " << matrix(2, 3) << std::endl;
			stream << "  " << matrix(3, 0) << ", " << matrix(3, 1) << ", " << matrix(3, 2) << ", " << matrix(3, 3) << " )";
			return stream;
		}
	}
}
