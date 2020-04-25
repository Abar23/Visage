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
			return angleInDegrees * (F_PI / 180.0f);
		}

		inline float FastInverseSqurRootAroundOne(float value)
		{
			constexpr float coeffOne = 35.0f / 16.0f;
			constexpr float coeffTwo = -35.0f / 16.0f;
			constexpr float coeffThree = 21.0f / 16.0f;
			constexpr float coeffFour = -5.0f / 16.0f;
			const float value2 = value * value;

			return coeffOne + coeffTwo * value + coeffThree * value2 + coeffFour * value2 * value;
		}
	}
}