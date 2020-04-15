#pragma once

#include <cmath>

namespace Visage
{
	namespace Math
	{
		bool FloatIsEqual(float floatOne, float floatTwo);

		inline float DegreesToRad(float angleInDegrees)
		{
			return angleInDegrees * (M_PI / 180.0f);
		}

		inline float RadToDegrees(float angleInDegrees)
		{
			return angleInDegrees * (M_PI / 180.0f);
		}
	}
}