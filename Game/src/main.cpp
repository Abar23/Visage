#include "Math/Vec3.h"
#include "Math/Vec4.h"
#include "Math/Vec2.h"
#include "Math/Mat3.h"
#include "Math/Mat4.h"
#include "Math/Mat3x4.h"
#include "Math/Quaternion.h"
#include "Math/MathFunctions.h"
#include "Math/DualQuaternion.h"

#include <chrono>
#include <iostream>

using namespace Visage;

int main()
{
	vec2 v(1.2f, 0.0f);
	std::cout << v.Normalized() << std::endl;
	std::cout << v.Renormalized() << std::endl;
	std::cout << v.Negated() << std::endl;
	std::cout << v.Magnitude() << std::endl;
	std::cout << v.SqrMagnitude() << std::endl;
	std::cout << vec2::Dot(vec2(1.0, 0.0), vec2(-1.0, 0.0)) << std::endl;
	std::cout << vec2::Project(vec2(0.5, 0.5), vec2(1.0, 0.0)) << std::endl;
	std::cout << (v == vec2(0.5, 0.5)) << std::endl;
	vec3 b = { 1, 2, 3 };
	vec4 g = { 1, 2, 3, 4 };

	vec2 c(v.yx);
	ivec2 h(1, 2);
	vec3 p = c.yyx;
	std::cout << (sizeof(p) / sizeof(float)) << std::endl;

	mat4 m(1.0f);
	m.SetTranslation(c.yyy);
	std::cout << m;
	return 0;
}