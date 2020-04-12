#include "Math/Vector3D.h"
#include <iostream>

int main()
{
	Visage::Math::Vector3D vector1(4.0f); 
	Visage::Math::Vector3D vector2(1.0f, 2.0f, 3.0f);
	Visage::Math::Vector3D vector4(1.0f, 2.0f, 3.0f);
	Visage::Math::Vector3D vector3;
	std::cout << vector1 << std::endl;
	std::cout << vector2 << std::endl;
	std::cout << vector3 << std::endl;
	std::cout << (vector4 == vector2) << std::endl;


	return 0;
}