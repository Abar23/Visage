#include <cstdint>
#include <cstring>
#include "MathFunctions.h"
#include "MathConstants.h"

namespace Visage
{
    namespace Math
    {
        bool FloatIsEqual(float floatOne, float floatTwo)
        {
            float absDiff = std::fabs(floatOne - floatTwo);
            if (absDiff <= maxEpsilonDiff)
            {
                return true;
            }

            int32_t a;
            int32_t b;
            memcpy(&a, &floatOne, sizeof(int));
            memcpy(&b, &floatTwo, sizeof(int));
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
