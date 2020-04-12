#include "Math/Vector3D.h"
#include "Math/Vector4D.h"
#include "Math/Vector2D.h"

#include <iostream>

using namespace Visage::Math;

int main()
{
	Vector3D vector1(4.0f); 
	Vector3D vector2(1.0f, 0.0f, 0.0f);
	Vector4D vector3(1.0f, 1.0f, 0.0f);
	Vector2D vector4(1.0f, 1.0f);
	Vector2D vector5(1.0f, 0.0f);
	std::cout << vector1 << std::endl;
	std::cout << vector2 << std::endl;
	std::cout << vector3 << std::endl;
	std::cout << vector4.Normalize().Magnitude() << std::endl;


	return 0;
}