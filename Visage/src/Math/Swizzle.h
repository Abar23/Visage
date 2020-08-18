#pragma once

#include <array>
#include <ostream>
#include <assert.h>

namespace Visage
{
	namespace Math
	{

		template <template <typename> class vectorType, typename T, int numberOfElements, int... Indices>
		class Swizzle
		{
		private:
			std::array<T, numberOfElements> data;

		public:
			vectorType<T>& operator=(const vectorType<T>& vector)
			{
				assert(vector.data.size() == numberOfElements);

				T indices[Indices...];

				for (unsigned int i = 0; i < this->data.size(); i++)
				{
					this->data[indices[i]] = vector[i];
				}

				return *(vectorType<T>*)this;
			}

			inline operator vectorType<T>() const
			{
				return vectorType<T>(data[Indices]...);
			}

			inline vectorType<T>& operator+=(const vectorType<T>& vector)
			{
				return *(reinterpret_cast<vectorType<T>*>(this)) += vector;
			}

			inline vectorType<T>& operator-=(const vectorType<T>& vector)
			{
				return *(reinterpret_cast<vectorType<T>*>(this)) -= vector;
			}

			inline vectorType<T>& operator*=(const T scalar)
			{
				return *(reinterpret_cast<vectorType<T>*>(this)) *= scalar;
			}

			inline vectorType<T>& operator/=(const T scalar)
			{
				return *(reinterpret_cast<vectorType<T>*>(this)) /= scalar;
			}
		};
	}
}
