#include "DoubleFrameAllocator.h"

namespace Visage
{
	namespace Core
	{		
		DoubleFrameAllocator::DoubleFrameAllocator(std::size_t sizeOfBuffers)
			: stacks{{sizeOfBuffers}, {sizeOfBuffers}}, activeBuffer(0)
		{ }
		
		DoubleFrameAllocator::~DoubleFrameAllocator()
		{
			stacks[0].ClearStack();
			stacks[1].ClearStack();
		}
	}
}
