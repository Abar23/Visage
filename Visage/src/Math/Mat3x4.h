#pragma once

#include <array>
#include <initializer_list>
#include "Vec4.h"
#include "Mat3.h"
#include "Mat4.h"

namespace Visage
{
	namespace Math
	{
		template <typename T>
		class Mat3x4
		{
		public:
			union
			{
				T data[4][3];

				Vec3<T> columns[4];
			};

			Mat3x4();
			Mat3x4(std::initializer_list<T> args);
			Mat3x4(const T m00, const T m01, const T m02, const T m03,
				   const T m10, const T m11, const T m12, const T m13,
				   const T m20, const T m21, const T m22, const T m23);
			Mat3x4(const Vec4<T>& firstRow,
				   const Vec4<T>& secondRow,
				   const Vec4<T>& thirdRow);
			Mat3x4(T diagonal);
			Mat3x4(const Mat3x4<T>& matrix);

			~Mat3x4() = default;

			Mat3x4<T> Inverted() const;
			Mat3x4<T>& Invert();
			Mat4<T> TransposeMatrix() const;
			T Determinant() const;
			Vec3<T> GetColumn(const int columnIndex) const;
			void SetColumn(const int columnIndex, const Vec3<T>& vector);
			Vec4<T> GetRow(const int rowIndex) const;
			void SetRow(const int rowIndex, const Vec4<T>& vector);
			Vec3<T> GetTranslation() const;
			void SetTranslation(const Vec3<T>& translation);
			Mat3<T> AffineMatrix() const;
			Mat3<T> NormalMatrix() const;
			Mat4<T> ToMat4() const;

			static Mat3x4<T> MakeRotationX(const T angleInDegrees);
			static Mat3x4<T> MakeRotationY(const T angleInDegrees);
			static Mat3x4<T> MakeRotationZ(const T angleInDegrees);
			static Mat3x4<T> MakeRotation(const Vec3<T>& axis, const T angleInDegrees);
			static Mat3x4<T> MakeScale(const T uniformScale);
			static Mat3x4<T> MakeScale(const T scaleX, const T scaleY, const T scaleZ);
			static Mat3x4<T> MakeScale(const Vec3<T>& vector);
			static Mat3x4<T> MakeTranslation(const T uniformTranslation);
			static Mat3x4<T> MakeTranslation(const T translationX, const T translationY, const T translationZ);
			static Mat3x4<T> MakeTranslation(const Vec3<T>& vector);
			static Mat3x4<T> LookAt(const Vec3<T>& cameraPosition, const Vec3<T>& targetPosition, const Vec3<T>& up);
			static Mat3x4<T> Orthographic(const T left, const T right, const T bottom, const T top, const T near, const T far);
			static Mat3x4<T> Identity();

			Mat3x4<T>& operator=(const Mat3x4<T>& matrix);

			const T& operator()(const int rowIndex, const int columnIndex) const;
			T& operator()(const int rowIndex, const int columnIndex);

			Mat3x4<T>& operator*=(const Mat3x4<T>& matrix);
			Mat3x4<T>& operator*=(const T scalar);

			friend Vec4<T> operator*(const Mat3x4<T>& matrix, const Vec4<T>& vector)
			{
				return Vec4<T>(matrix(0, 0) * vector.x + matrix(1, 0) * vector.y + matrix(2, 0) * vector.z + matrix(3, 0) * vector.w,
							   matrix(0, 1) * vector.x + matrix(1, 1) * vector.y + matrix(2, 1) * vector.z + matrix(3, 1) * vector.w,
							   matrix(0, 2) * vector.x + matrix(1, 2) * vector.y + matrix(2, 2) * vector.z + matrix(3, 2) * vector.w,
							   vector.w);
			}


			friend Vec3<T> operator*(const Mat3x4<T>& matrix, const Vec3<T>& vector)
			{
				return Vec3<T>(matrix(0, 0) * vector.x + matrix(1, 0) * vector.y + matrix(2, 0) * vector.z,
							   matrix(0, 1) * vector.x + matrix(1, 1) * vector.y + matrix(2, 1) * vector.z,
							   matrix(0, 2) * vector.x + matrix(1, 2) * vector.y + matrix(2, 2) * vector.z);
			}
		};

		template <typename T>
		Mat3x4<T> operator*(const Mat3x4<T>& leftMatrix, const Mat3x4<T>& rightMatrix);

		template <typename T>
		Mat4<T> operator*(const Mat3x4<T>& leftMatrix, const Mat4<T>& rightMatrix);

		template <typename T>
		Mat4<T> operator*(const Mat4<T>& leftMatrix, const Mat3x4<T>& rightMatrix);

		template <typename T>
		Mat3x4<T> operator*(const Mat3x4<T>& matrix, const T scalar);

		template <typename T>
		Mat3x4<T> operator*(const T scalar, const Mat3x4<T>& matrix);

		template <typename T>
		std::ostream& operator<<(std::ostream& stream, const Mat3x4<T>& matrix);
	}

	using mat3x4 = Math::Mat3x4<float>;
	using dmat3x4 = Math::Mat3x4<double>;
}

#include "Mat3x4.inl"
