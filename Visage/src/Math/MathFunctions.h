#pragma once

#include <cstdint>
#include <cmath>
#include <cstring>

#include "MathConstants.h"

namespace Visage
{
	namespace Math
	{
        inline bool FloatIsEqual(float A, float B)
        {
            float absDiff = std::fabs(A - B);
            if (absDiff <= maxEpsilonDiff)
            {
                return true;
            }

            int32_t a;
            int32_t b;
            memcpy(&a, &A, sizeof(int));
            memcpy(&b, &B, sizeof(int));
            if ((a < 0) != (b < 0))
            {
                return false;
            }

            int ulpsDiff = std::abs(a - b);
            if (ulpsDiff <= maxUlpsDiff)
            {
                return true;
            }

            return false;
        }
	}
}