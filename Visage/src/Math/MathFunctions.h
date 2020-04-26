#pragma once

#include "MathConstants.h"

namespace Visage
{
	namespace Math
	{
		bool FloatIsEqual(float floatOne, float floatTwo);

		inline float DegreesToRad(float angleInDegrees)
		{
			return angleInDegrees * (F_PI / 180.0f);
		}

		inline float RadToDegrees(float angleInDegrees)
		{
			return angleInDegrees * (180.0f / F_PI);
		}

		inline float FastInverseSqurRootAroundOne(float value)
		{
			constexpr float coeffOne = 15.0f / 8.0f;
			constexpr float coeffTwo = -5.0f / 4.0f;
			constexpr float coeffThree = 3.0f / 8.0f;

			return coeffOne + coeffTwo * value + coeffThree * value * value;
		}
	}
}