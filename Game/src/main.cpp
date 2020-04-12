#include "Math/Vector3D.h"
#include <iostream>

using namespace Visage::Math;

int main()
{
	Vector3D vector1(4.0f); 
	Vector3D vector2(1.0f, 0.0f, 0.0f);
	Vector3D vector4(1.0f, 1.0f, 0.0f);
	Vector3D vector3;
	std::cout << vector1 << std::endl;
	std::cout << vector2 << std::endl;
	std::cout << vector3 << std::endl;
	std::cout << vector4[3] << std::endl;


	return 0;
}