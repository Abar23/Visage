#pragma once

#include <cstring>
#include <cmath>
#include "MathFunctions.h"
#include "Mat4.h"

namespace Visage
{
	namespace Math
	{
		template <typename T>
		Mat4<T>::Mat4()
			: entries{ 0 } 
		{
		}

		template <typename T>
		Mat4<T>::Mat4(const T m00, const T m01, const T m02, const T m03,
				      const T m10, const T m11, const T m12, const T m13, 
				      const T m20, const T m21, const T m22, const T m23, 
				      const T m30, const T m31, const T m32, const T m33)
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

		template <typename T>
		Mat4<T>::Mat4(const Vec4<T>& firstRow,
				      const Vec4<T>& secondRow, 
				      const Vec4<T>& thirdRow, 
				      const Vec4<T>& fourthRow)
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

		template <typename T>
		Mat4<T>::Mat4(const T diagonal)
			: entries{ 0 }
		{
			entries[0][0] = diagonal;
			entries[1][1] = diagonal;
			entries[2][2] = diagonal;
			entries[3][3] = diagonal;
		}

		template <typename T>
		Mat4<T>::Mat4(const Mat4<T>& matrix)
		{
			std::memcpy(entries, matrix.entries, sizeof(Mat4<T>));
		}

		template <typename T>
		Mat4<T> Mat4<T>::Inverted() const
		{
			const Vec3<T> a = reinterpret_cast<const Vec3<T>&>(entries[0]);
			const Vec3<T> b = reinterpret_cast<const Vec3<T>&>(entries[1]);
			const Vec3<T> c = reinterpret_cast<const Vec3<T>&>(entries[2]);
			const Vec3<T> d = reinterpret_cast<const Vec3<T>&>(entries[3]);

			T x = entries[0][3];
			T y = entries[1][3];
			T z = entries[2][3];
			T w = entries[3][3];

			Vec3<T> s = Vec3<T>::Cross(a, b);
			Vec3<T> t = Vec3<T>::Cross(c, d);
			Vec3<T> u = a * y - b * x;
			Vec3<T> v = c * w - d * z;

			T inverseDet = static_cast<T>(1) / Vec3<T>::Dot(s, v) - Vec3<T>::Dot(t, u);
			s *= inverseDet;
			t *= inverseDet;
			u *= inverseDet;
			v *= inverseDet;

			Vec3<T> firstRow = Vec3<T>::Cross(b, v) + t * y;
			Vec3<T> secondRow = Vec3<T>::Cross(v, a) - t * x;
			Vec3<T> thirdRow = Vec3<T>::Cross(d, u) + s * w;
			Vec3<T> fourthRow = Vec3<T>::Cross(u, c) - s * z;

			return Mat4<T>(firstRow.x, firstRow.y, firstRow.z, -Vec3<T>::Dot(b, t),
						   secondRow.x, secondRow.y, secondRow.z, Vec3<T>::Dot(a, t),
						   thirdRow.x, thirdRow.y, thirdRow.z, -Vec3<T>::Dot(d, s),
						   fourthRow.x, fourthRow.y, fourthRow.z, Vec3<T>::Dot(c, s));
		}

		template <typename T>
		Mat4<T>& Mat4<T>::Invert()
		{
			const Vec3<T> a = reinterpret_cast<const Vec3<T>&>(entries[0]);
			const Vec3<T> b = reinterpret_cast<const Vec3<T>&>(entries[1]);
			const Vec3<T> c = reinterpret_cast<const Vec3<T>&>(entries[2]);
			const Vec3<T> d = reinterpret_cast<const Vec3<T>&>(entries[3]);

			T x = entries[0][3];
			T y = entries[1][3];
			T z = entries[2][3];
			T w = entries[3][3];

			Vec3<T> s = Vec3<T>::Cross(a, b);
			Vec3<T> t = Vec3<T>::Cross(c, d);
			Vec3<T> u = a * y - b * x;
			Vec3<T> v = c * w - d * z;

			T inverseDet = static_cast<T>(1) / Vec3<T>::Dot(s, v) - Vec3<T>::Dot(t, u);
			s *= inverseDet;
			t *= inverseDet;
			u *= inverseDet;
			v *= inverseDet;

			Vec3<T> firstRow = Vec3<T>::Cross(b, v) + t * y;
			Vec3<T> secondRow = Vec3<T>::Cross(v, a) - t * x;
			Vec3<T> thirdRow = Vec3<T>::Cross(d, u) + s * w;
			Vec3<T> fourthRow = Vec3<T>::Cross(u, c) - s * z;

			entries[0][0] = firstRow.x;
			entries[1][0] = firstRow.y;
			entries[2][0] = firstRow.z;
			entries[3][0] = -Vec3<T>::Dot(b, t);

			entries[0][1] = secondRow.x;
			entries[1][1] = secondRow.y;
			entries[2][1] = secondRow.z;
			entries[3][1] = -Vec3<T>::Dot(a, t);

			entries[0][2] = thirdRow.x;
			entries[1][2] = thirdRow.y;
			entries[2][2] = thirdRow.z;
			entries[3][2] = -Vec3<T>::Dot(d, s);

			entries[0][3] = fourthRow.x;
			entries[1][3] = fourthRow.y;
			entries[2][3] = fourthRow.z;
			entries[3][3] = -Vec3<T>::Dot(c, s);

			return *this;
		}

		template <typename T>
		Mat4<T> Mat4<T>::Transposed() const
		{
			return Mat4<T>(entries[0][0], entries[0][1], entries[0][2], entries[0][3],
						   entries[1][0], entries[1][1], entries[1][2], entries[1][3],
						   entries[2][0], entries[2][1], entries[2][2], entries[2][3],
						   entries[3][0], entries[3][1], entries[3][2], entries[3][3]);
		}

		template <typename T>
		Mat4<T>& Mat4<T>::Transpose()
		{
			Mat4<T> temp = *this;

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

		template <typename T>
		float Mat4<T>::Determinant() const
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

		template <typename T>
		Vec4<T> Mat4<T>::GetColumn(const int columnIndex) const
		{
			return Vec4<T>(entries[columnIndex][0], 
						   entries[columnIndex][1], 
						   entries[columnIndex][2],
						   entries[columnIndex][3]);
		}

		template <typename T>
		void Mat4<T>::SetColumn(const int columnIndex, const Vec4<T>& vector)
		{
			entries[columnIndex][0] = vector.x;
			entries[columnIndex][1] = vector.y;
			entries[columnIndex][2] = vector.z;
			entries[columnIndex][3] = vector.w;
		}

		template <typename T>
		Vec4<T> Mat4<T>::GetRow(const int rowIndex) const
		{
			return Vec4<T>(entries[0][rowIndex], 
						   entries[1][rowIndex], 
						   entries[2][rowIndex], 
						   entries[3][rowIndex]);
		}

		template <typename T>
		void Mat4<T>::SetRow(const int rowIndex, const Vec4<T>& vector)
		{
			entries[0][rowIndex] = vector.x;
			entries[1][rowIndex] = vector.y;
			entries[2][rowIndex] = vector.z;
			entries[3][rowIndex] = vector.w;
		}

		template <typename T>
		Vec3<T> Mat4<T>::GetTranslation() const
		{
			return Vec3<T>(entries[3][0], 
						   entries[3][1], 
						   entries[3][2]);
		}

		template <typename T>
		void Mat4<T>::SetTranslation(const Vec3<T>& translation)
		{
			entries[3][0] = translation.x;
			entries[3][1] = translation.y;
			entries[3][2] = translation.z;
		}

		template <typename T>
		Mat3<T> Mat4<T>::AffineMatrix() const
		{
			return Mat3<T>(entries[0][0], entries[1][0], entries[2][0],
						   entries[0][1], entries[1][1], entries[2][1], 
						   entries[0][2], entries[1][2], entries[2][2]);
		}

		template <typename T>
		Mat3<T> Mat4<T>::NormalMatrix() const
		{
			return AffineMatrix().Inverted().Transposed();
		}

		template <typename T>
		Mat4<T> Mat4<T>::MakeRotationX(const T angleInDegrees)
		{
			T radians = DegreesToRad(angleInDegrees);
			T cos = std::cos(radians);
			T sin = std::sin(radians);

			return Mat4<T>(1, 0, 0, 0,
						   0, cos, -sin, 0,
						   0, sin, cos, 0,
						   0, 0, 0, 1);
		}

		template <typename T>
		Mat4<T> Mat4<T>::MakeRotationY(const T angleInDegrees)
		{
			T radians = DegreesToRad(angleInDegrees);
			T cos = std::cos(radians);
			T sin = std::sin(radians);

			return Mat4<T>(cos, 0, sin, 0,
						   0, 1, 0, 0,
						   -sin, 0, cos, 0,
						   0, 0, 0, 1);
		}

		template <typename T>
		Mat4<T> Mat4<T>::MakeRotationZ(const T angleInDegrees)
		{
			T radians = DegreesToRad(angleInDegrees);
			T cos = std::cos(radians);
			T sin = std::sin(radians);

			return Mat4<T>(cos, -sin, 0, 0,
						   sin, cos, 0, 0,
						   0, 0, 1, 0,
						   0, 0, 0, 1);
		}

		template <typename T>
		Mat4<T> Mat4<T>::MakeRotation(const Vec3<T>& axis, const T angleInDegrees)
		{
			T radians = DegreesToRad(angleInDegrees);
			T cos = std::cos(radians);
			T sin = std::sin(radians);
			T oneMinsCos = static_cast<T>(1) - cos;

			T x = axis.x * oneMinsCos;
			T y = axis.y * oneMinsCos;
			T z = axis.z * oneMinsCos;
			T axisXAxisY = x * axis.y;
			T axisXAxisZ = x * axis.z;
			T axisYAxisZ = y * axis.z;

			return Mat4<T>(cos + x * axis.x, axisXAxisY - sin * axis.z, axisXAxisZ + sin * axis.y, 0,
						   axisXAxisY + sin * axis.z, cos + y * axis.y, axisYAxisZ - sin * axis.x, 0,
						   axisXAxisZ - sin * axis.y, axisYAxisZ + sin * axis.x, cos + z * axis.z, 0,
						   0, 0, 0, 1);
		}

		template <typename T>
		Mat4<T> Mat4<T>::MakeScale(const T uniformScale)
		{
			return Mat4<T>(uniformScale, 0, 0, 0,
						   0, uniformScale, 0, 0,
						   0, 0, uniformScale, 0,
						   0, 0, 0, 1);
		}

		template <typename T>
		Mat4<T> Mat4<T>::MakeScale(const T scaleX, const T scaleY, const T scaleZ)
		{
			return Mat4<T>(scaleX, 0, 0, 0,
						   0, scaleY, 0, 0,
						   0, 0, scaleZ, 0,
						   0, 0, 0, 1);		
		}

		template <typename T>
		Mat4<T> Mat4<T>::MakeScale(const Vec3<T>& vector)
		{
			return Mat4<T>(vector.x, 0, 0, 0,
						   0, vector.y, 0, 0,
						   0, 0, vector.z, 0,
						   0, 0, 0, 1);
		}

		template <typename T>
		Mat4<T> Mat4<T>::MakeTranslation(const T uniformTranslation)
		{
			return Mat4<T>(1, 0, 0, uniformTranslation,
						   0, 1, 0, uniformTranslation,
						   0, 0, 1, uniformTranslation,
						   0, 0, 0, 1);	
		}

		template <typename T>
		Mat4<T> Mat4<T>::MakeTranslation(const T translationX, const T translationY, const T translationZ)
		{
			return Mat4<T>(1, 0, 0, translationX,
						   0, 1, 0, translationY,
						   0, 0, 1, translationZ,
						   0, 0, 0, 1);			
		}

		template <typename T>
		Mat4<T> Mat4<T>::MakeTranslation(const Vec3<T>& vector)
		{
			return Mat4<T>(1, 0, 0, vector.x,
						   0, 1, 0, vector.y,
						   0, 0, 1, vector.z,
						   0, 0, 0, 1);	
		}

		template <typename T>
		Mat4<T> Mat4<T>::LookAt(const Vec3<T>& cameraPosition, const Vec3<T>& targetPosition, const Vec3<T>& up)
		{
			Vec3<T> forwardAxis = (cameraPosition - targetPosition).Normalize();
			Vec3<T> rightAxis = Vec3<T>::Cross(up, forwardAxis).Normalize();
			Vec3<T> upAxis = Vec3<T>::Cross(forwardAxis, rightAxis).Normalize();
			
			return Mat4<T>(rightAxis.x, rightAxis.y, rightAxis.z, -Vec3<T>::Dot(rightAxis, cameraPosition),
						   upAxis.x, upAxis.y, upAxis.z, -Vec3<T>::Dot(upAxis, cameraPosition),
						   forwardAxis.x, forwardAxis.y, forwardAxis.z, -Vec3<T>::Dot(forwardAxis, cameraPosition),
						   0, 0, 0, 1);
		}

		template <typename T>
		Mat4<T> Mat4<T>::Orthographic(const T left, const T right, const T bottom, const T top, const T near, const T far)
		{
			return Mat4<T>(static_cast<T>(2) / (right - left), 0, 0, (left + right) / (left - right),
						   0, static_cast<T>(2) / (top - bottom), 0, (bottom + top) / (bottom - top),
						   0, 0, static_cast<T>(2) / (near - far), (near + far) / (far - near),
						   0, 0, 0, 1);
		}

		template <typename T>
		Mat4<T> Mat4<T>::Perspective(const T fieldOfViewInDegrees, const T aspectRatio, const T near, const T far)
		{
			T c = static_cast<T>(1) / std::tan(fieldOfViewInDegrees / static_cast<T>(2));
			T farMinusNear = far - near;

			return Mat4<T>(c / aspectRatio, 0, 0, 0,
						   0, c, 0, 0,
						   0, 0, static_cast<T>(-1) * (far + near) / (farMinusNear), static_cast<T>(-2) * far * near / farMinusNear,
						   0, 0, -1, 0);
		}

		template <typename T>
		Mat4<T> Mat4<T>::Identity()
		{
			return Mat4<T>(1);
		}

		template <typename T>
		Mat4<T>& Mat4<T>::operator=(const Mat4<T>& matrix)
		{
			std::memcpy(entries, matrix.entries, sizeof(Mat4<T>));
			return *this;
		}

		template<typename T>
		const T& Mat4<T>::operator()(const int rowIndex, const int columnIndex) const
		{
			return entries[columnIndex][rowIndex];
		}

		template<typename T>
		T& Mat4<T>::operator()(const int rowIndex, const int columnIndex)
		{
			return entries[columnIndex][rowIndex];
		}

		template <typename T>
		Mat4<T>& Mat4<T>::operator*=(const Mat4<T>& matrix)
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

		template <typename T>
		Mat4<T>& Mat4<T>::operator*=(const T scalar)
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

		template <typename T>
		Mat4<T> operator*(const Mat4<T>& leftMatrix, const Mat4<T>& rightMatrix)
		{
			Mat4<T> leftMatrixCopy = leftMatrix;
			return leftMatrixCopy *= rightMatrix;
		}

		template <typename T>
		Vec4<T> operator*(const Mat4<T>& matrix, const Vec4<T>& vector)
		{
			return Vec4<T>(matrix(0, 0) * vector.x + matrix(1, 0) * vector.y + matrix(2, 0) * vector.z + matrix(3, 0) * vector.w,
						   matrix(0, 1) * vector.x + matrix(1, 1) * vector.y + matrix(2, 1) * vector.z + matrix(3, 1) * vector.w,
						   matrix(0, 2) * vector.x + matrix(1, 2) * vector.y + matrix(2, 2) * vector.z + matrix(3, 2) * vector.w,
						   matrix(0, 3) * vector.x + matrix(1, 3) * vector.y + matrix(2, 3) * vector.z + matrix(3, 3) * vector.w);
		}

		template <typename T>
		Mat4<T> operator*(const Mat4<T>& matrix, const T scalar)
		{
			Mat4<T> matrixCopy = matrix;
			return matrixCopy *= scalar;
		}

		template<typename T>
		Mat4<T> operator*(const T scalar, const Mat4<T>& matrix)
		{
			Mat4<T> matrixCopy = matrix;
			return matrixCopy *= scalar;
		}

		template <typename T>
		std::ostream& operator<<(std::ostream& stream, const Mat4<T>& matrix)
		{
			stream << "( " << matrix(0, 0) << ", " << matrix(0, 1) << ", " << matrix(0, 2) << ", " << matrix(0, 3) << std::endl;
			stream << "  " << matrix(1, 0) << ", " << matrix(1, 1) << ", " << matrix(1, 2) << ", " << matrix(1, 3) << std::endl;
			stream << "  " << matrix(2, 0) << ", " << matrix(2, 1) << ", " << matrix(2, 2) << ", " << matrix(2, 3) << std::endl;
			stream << "  " << matrix(3, 0) << ", " << matrix(3, 1) << ", " << matrix(3, 2) << ", " << matrix(3, 3) << " )";
			return stream;
		}
	}
}
