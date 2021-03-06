#pragma once

#include "StackAllocator.h"
#include <cstddef>
#include <utility>

namespace Visage
{
	namespace Core
	{
		class DoubleFrameAllocator
		{
		private:
			StackAllocator stacks[2];
			std::uint8_t activeBuffer;

		public:
			DoubleFrameAllocator() = delete;

			DoubleFrameAllocator(std::size_t sizeOfBuffers);

			inline void SwapBuffers()
			{
				activeBuffer = (activeBuffer == 0) ? 1 : 0;
			}

			inline void ClearCurrentBuffer()
			{
				stacks[activeBuffer].ClearStack();
			}

			inline std::size_t GetMemoryUsed()
			{
				return stacks[0].GetMemoryUsed() + stacks[1].GetMemoryUsed();
			}

			inline std::size_t GetNumberOfAllocations()
			{
				return stacks[0].GetNumberOfAllocations() + stacks[1].GetNumberOfAllocations();
			}

			template <typename T>
			T* New()
			{
				return stacks[activeBuffer].New<T>();
			}

			template <typename T, typename... Args>
			T* NewWithArgs(Args&&... args)
			{
				return stacks[activeBuffer].NewWithArgs<T>(std::forward<Args>(args)...);
			}

			template <typename T>
			T* NewArray(std::size_t arrayLength)
			{
				return stacks[activeBuffer].NewArray<T>(arrayLength);
			}
		};
	}
}
