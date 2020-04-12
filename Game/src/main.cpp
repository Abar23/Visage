#include "Math/Vector3D.h"
#include "Math/Vector4D.h"
#include <iostream>

int main()
{
	Visage::Math::Vector3D vector1(4.0f); 
	Visage::Math::Vector3D vector2(1.0f, 0.0f, 0.0f);
	Visage::Math::Vector4D vector4(1.0f, 1.0f, 0.0f);
	Visage::Math::Vector3D vector3;
	std::cout << vector1 << std::endl;
	std::cout << vector2 << std::endl;
	std::cout << vector4 << std::endl;


	return 0;
}