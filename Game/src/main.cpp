#include "Math/Vector3D.h"
#include "Math/Vector4D.h"
#include "Math/Vector2D.h"
#include "Math/Matrix3D.h"
#include "Math/Matrix4D.h"

#include <iostream>
#include <chrono> 

using namespace Visage::Math;

int main()
{
	Vector3D vector1(4.0f); 
	Vector3D vector2(1.0f, 0.0f, 0.0f);
	Vector4D vector3(1.0f, 1.0f, 0.0f);
	Vector2D vector4(1.0f, 1.0f);
	Vector2D vector5(1.0f, 0.0f);
	Matrix3D m1(1, 2, 3, 4, 5, 6, 7, 2, 9);
	Matrix3D m2;
	Matrix4D m3(1.0f);

	std::cout << vector1 << std::endl;
	std::cout << vector2 << std::endl;
	std::cout << vector3 << std::endl;
	std::cout << vector4.Normalize().Magnitude() << std::endl;
	std::cout << m1.MakeRotationX(0) * Matrix3D::Identity() << std::endl;
	std::cout << m1.MakeRotaion(0, Vector3D::XAxis()) * Matrix3D::Identity() << std::endl;

	auto start = std::chrono::high_resolution_clock::now();
	Matrix3D::MakeRotationX(30);
	auto stop = std::chrono::high_resolution_clock::now();;
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << duration.count() << std::endl;

	return 0;
}