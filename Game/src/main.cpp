#include "Math/Vec3.h"
#include "Math/Vec4.h"
#include "Math/Vec2.h"
#include "Math/Mat3.h"
#include "Math/Mat4.h"
#include "Math/Quaternion.h"
#include "Math/MathFunctions.h"
#include "Math/DualQuaternion.h"

#include <chrono>
#include <iostream>

using namespace Visage::Math;

int main()
{
	Mat4 m(Vec4(2.0f, 2.0f, 2.0f, 2.0f), Vec4::Zero(), Vec4::Zero(), Vec4::Zero());
	std::cout << m;
	return 0;
}