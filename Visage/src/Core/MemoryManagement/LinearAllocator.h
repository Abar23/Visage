#pragma once

#include "AbstractAllocator.h"
#include <cstddef>
#include <cstdint>

namespace Visage
{
	namespace Core
	{
		class LinearAllocator : public AbstractAllocator
		{
		private:
			void* currentPosition;
			void* endOfBuffer;

		protected:
			void* Allocate(std::size_t size, std::uint8_t align) override;

			void Deallocate(void*& pointer) override;

		public:
			LinearAllocator() = delete;

			LinearAllocator(std::size_t size);

			void Reset();

			template <typename T>
			T* New()
			{
				return new (Allocate(sizeof(T), alignof(T))) T;
			}

			template <typename T, typename... Args>
			T* NewWithArgs(Args&&... args)
			{
				return new (Allocate(sizeof(T), alignof(T))) T(std::forward<Args>(args)...);
			}

			template <typename T>
			T* NewArray(std::size_t arrayLength)
			{
				std::uint8_t numberOfElementsForOneWord = sizeof(size_t) / sizeof(T);

				if (sizeof(size_t) > (static_cast<std::size_t>(numberOfElementsForOneWord) * sizeof(T)))
				{
					numberOfElementsForOneWord += 1;
				}

				T* baseArrayAddress = reinterpret_cast<T*>(Allocate((arrayLength + numberOfElementsForOneWord) * sizeof(T), alignof(T))) + numberOfElementsForOneWord;
				*(reinterpret_cast<std::size_t*>(baseArrayAddress) - 1) = arrayLength;

				for (std::size_t i = 0; i < arrayLength; i++)
				{
					new (&baseArrayAddress[i]) T;
				}

				return baseArrayAddress;
			}
		};
	}
}

