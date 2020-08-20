#include "Math/Math.h"

#include <chrono>
#include <iostream>

int main()
{
	Visage::vec4 v = {1.0f, 0.0f, 3.0f, 4.0f};
	Visage::ivec2 i = {1, 2};
	Visage::vec2 c = v.xy;

	Visage::mat3 m(c.xyy, c.yxy, c.yyx);

	v = c.xxyy;

	Visage::mat4 t(c.xyyy, c.xxyy, c.xxxx, c.yyyy);

	Visage::mat3 k = { 1, 2, 3, 
					   4, 5, 6, 
					   7, 8, 9};
	Visage::mat3x4 l = { 1, 2, 3, 4, 
						 5, 6, 7, 8, 
						 9, 10, 11, 12};
	Visage::mat4 b = { 1, 2, 3, 4, 
					   5, 6, 7, 8, 
					   9, 10, 11, 12, 
					   13, 14, 15, 16 };

	return 0;
}