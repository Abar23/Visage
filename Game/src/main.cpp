#include "Math/Vector3D.h"
#include "Math/Vector4D.h"
#include "Math/Vector2D.h"
#include "Math/Matrix3D.h"
#include "Math/Matrix4D.h"
#include "Math/Quaternion.h"
#include "Math/MathFunctions.h"

#include <chrono>
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
	std::cout << m1.Inverted().Transposed() * Matrix3D::Identity() << std::endl;
	std::cout << m3.NormalMatrix() << std::endl;
	std::cout << m3.Determinant() << std::endl;
	std::cout << m3.Inverted() << std::endl;
	std::cout << Matrix4D::Perspective(120, 16.0f/9.0f, 0.0f, 100.0f) * Matrix4D::LookAt(Vector3D(0.0f), Vector3D(0.0f, 0.0f, -1.0f), Vector3D::Up()) * Matrix4D(1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1) << std::endl;
	
	Quaternion q = Quaternion::MakeRotationZ(-90.0f);
	std::cout << q.Norm() << std::endl;
	std::cout << q.SqrNorm() << std::endl;
	std::cout << q.Normalized() << std::endl;
	std::cout << q.Inverted() << std::endl;
	std::cout << q.Conjugate() << std::endl;
	std::cout << Quaternion::TransformVector(q, Vector3D::Right())<< std::endl;
	std::cout << q.Normalized().GetRotationMatrix() * Vector3D::Right() << std::endl;
	std::cout << Matrix3D::MakeRotationZ(-90.0f) * Vector3D::Right() << std::endl;
	q.SetRotationMatrix(Matrix3D::MakeRotationZ(-90.0f));
	Quaternion q2 = Quaternion::MakeRotationZ(-90.0f);
	q2 = ((q2 * q2).Normalized() * q2).Normalized();
	std::cout << q2.Norm() << std::endl;

	std::cout << q2 << std::endl;
	auto t1 = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i <= 1000000; i++)
	{
		q.Renormalized();
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << duration / 1000000.0f << std::endl;

	return 0;
}