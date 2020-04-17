#include "Math/Vector3D.h"
#include "Math/Vector4D.h"
#include "Math/Vector2D.h"
#include "Math/Matrix3D.h"
#include "Math/Matrix4D.h"

#include <iostream>

using namespace Visage::Math;

int main()
{
	Vector3D vector1(4.0f); 
	Vector3D vector2(1.0f, 0.0f, 0.0f);
	Vector4D vector3(1.0f, 1.0f, 0.0f);
	Vector2D vector4(1.0f, 1.0f);
	Vector2D vector5(1.0f, 0.0f);
	Matrix3D m1(1, 2, 3, 0, 1, 0, 0, 0, 1);
	Matrix3D m2;
	Matrix4D m3(1.0f, 2.0f, 3.0f, 4.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
	Matrix4D m4(1.0f);
	std::cout << m1.Inverse().Transpose() * Matrix3D::Identity() << std::endl;
	std::cout << m3.NormalMatrix() << std::endl;
	std::cout << m3.Determinant() << std::endl;
	std::cout << m3.Inverse() << std::endl;
	std::cout << m4 * Matrix4D::Identity() << std::endl;

	return 0;
}