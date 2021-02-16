#include "StackAllocator.h"
#include "MemoryUtils.h"

namespace Visage
{
	namespace Core
	{
		StackAllocator::StackAllocator(std::size_t size)
			: AbstractAllocator(size)
		{ 
			topOfStackMarker = startOfBuffer;

			#ifdef DEBUG
				previousAddress = nullptr;
			#endif
		}

		StackAllocator::~StackAllocator()
		{
			this->topOfStackMarker = nullptr;

			#ifdef DEBUG
				this->previousAddress = nullptr;
			#endif
		}

		void* StackAllocator::Allocate(std::size_t size, std::uint8_t align)
		{
			void* alignedAddress = nullptr;
			std::uint8_t adjustment = AlignedPointerWithHeaderAdjustment(topOfStackMarker, align, allocationHeaderSize);

			if (memoryUsed + size + adjustment <= this->size)
			{
				alignedAddress = AddToPointer(topOfStackMarker, adjustment);

				AllocationHeader* header = reinterpret_cast<AllocationHeader*>(SubtractFromPointer(alignedAddress, allocationHeaderSize));
				header->adjustment = adjustment;

				topOfStackMarker = AddToPointer(alignedAddress, size);
				memoryUsed += size + adjustment;
				numberOfAllocations++;

				#ifdef DEBUG
					header->previousAddress = previousAddress;
					previousAddress = alignedAddress;
				#endif
			}

			return alignedAddress;
		}

		void StackAllocator::Deallocate(void*& pointer)
		{
			AllocationHeader* header = reinterpret_cast<AllocationHeader*>(SubtractFromPointer(pointer, allocationHeaderSize));

			#ifdef DEBUG
				assert(previousAddress == pointer);
				previousAddress = header->previousAddress;
			#endif
				
			memoryUsed -= PointerDiff(topOfStackMarker, pointer) + header->adjustment;
			numberOfAllocations--;	
			topOfStackMarker = SubtractFromPointer(pointer, header->adjustment);
		}

		void StackAllocator::ClearStack()
		{
			memoryUsed = 0;
			numberOfAllocations = 0;
			topOfStackMarker = startOfBuffer;
		}

		void* StackAllocator::GetTopOfStack()
		{
			return topOfStackMarker;
		}
	}
}