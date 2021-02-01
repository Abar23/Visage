#pragma once

#include <cstdint>
#include <cstddef>
#include <cassert>

namespace Visage
{
	namespace Core
	{
		inline std::uintptr_t AlignAddress(const std::uintptr_t address, const std::uint8_t align)
		{
			const std::size_t mask = align - 1;
			assert((mask & align) == 0); // Ensure that the align is power of 2
			return (mask + address) & ~mask;
		}

		inline void* AlignPointer(const void* pointer, const std::uint8_t align)
		{
			const std::uintptr_t address = reinterpret_cast<std::uintptr_t>(pointer);
			const std::uintptr_t alignedAddress = AlignAddress(address, align);
			return reinterpret_cast<void*>(alignedAddress);
		}

		inline std::uint8_t AlignedPointerAdjustment(const void* pointer, const std::uint8_t align)
		{
			const std::uintptr_t address = reinterpret_cast<std::uintptr_t>(pointer);
			return AlignAddress(address, align) - address;
		}

		inline std::uint8_t AlignedPointerWithHeaderAdjustment(const void* pointer, const std::uint8_t align, const std::size_t headerSize)
		{
			std::uint8_t adjustment = AlignedPointerAdjustment(pointer, align);

			if (adjustment < headerSize)
			{
				std::size_t requiredSpace = headerSize - adjustment;

				std::uint8_t numberOfAlignments = (requiredSpace / align);

				if (requiredSpace - (static_cast<std::size_t>(numberOfAlignments) * align) > 0)
				{
					numberOfAlignments += 1;
				}

				adjustment += numberOfAlignments * align;
			}

			return adjustment;
		}

		inline void* AddToPointer(const void* firstPointer, const std::size_t value)
		{
			return reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(firstPointer) + value);
		}

		inline void* SubtractFromPointer(const void* firstPointer, const std::size_t value)
		{
			return reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(firstPointer) - value);
		}

		inline std::uintptr_t PointerDiff(const void* firstPointer, const void* secondPointer)
		{
			return reinterpret_cast<std::uintptr_t>(firstPointer) - reinterpret_cast<std::uintptr_t>(secondPointer);
		}
	}
}