#pragma once

#include <cstddef>
#include <cstdint>
#include <cassert>
#include <utility>

namespace Visage
{
	namespace Core
	{
		class AbstractAllocator
		{
		protected:
			std::size_t sizeOfBuffer = 0;
			std::size_t numberOfAllocations;
			std::size_t memoryUsed;
			void* startOfBuffer;

			virtual void* Allocate(std::size_t size, std::uint8_t) = 0;
			virtual void Deallocate(void*& pointer) = 0;
			
		public:
			AbstractAllocator()
				: startOfBuffer(nullptr), numberOfAllocations(0), memoryUsed(0)
			{ }

			AbstractAllocator(std::size_t size)
				: sizeOfBuffer(size), numberOfAllocations(0), memoryUsed(0)
			{
				startOfBuffer = new std::uint8_t[size];
			}

			virtual ~AbstractAllocator()
			{
				#ifdef DEBUG
					assert(numberOfAllocations == 0 && memoryUsed == 0);
				#endif
				
				delete startOfBuffer;
			}
			
			std::size_t GetNumberOfAllocations()
			{
				return numberOfAllocations;
			}

			std::size_t GetMemoryUsed()
			{
				return memoryUsed;
			}
		};
	}
}
