#include "LinearAllocator.h"
#include "MemoryUtils.h"
#include <stdint.h>

namespace Visage
{
	namespace Core
	{	
		LinearAllocator::LinearAllocator(std::size_t size)
			: AbstractAllocator(size)
		{
			currentPosition = startOfBuffer;
			endOfBuffer = AddToPointer(startOfBuffer, sizeOfBuffer);
		}
		
		void* Visage::Core::LinearAllocator::Allocate(std::size_t size, std::uint8_t align)
		{
			void* alignedAddress = AlignPointer(currentPosition, align);
			currentPosition = AddToPointer(alignedAddress, size);

			if (reinterpret_cast<std::uintptr_t>(currentPosition) > reinterpret_cast<std::uintptr_t>(endOfBuffer))
			{
				return nullptr; // assert out of memory error
			}

			numberOfAllocations++;
			memoryUsed += size;

			return alignedAddress;
		}

		void LinearAllocator::Deallocate(void*& pointer)
		{ }

		void LinearAllocator::Reset()
		{
			memoryUsed = 0;
			numberOfAllocations = 0;
			currentPosition = startOfBuffer;
		}
	}
}
