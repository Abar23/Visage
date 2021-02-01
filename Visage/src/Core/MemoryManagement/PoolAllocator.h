#pragma once

#include "AbstractAllocator.h"
#include <cstddef>
#include <cstdint>

namespace Visage
{
	namespace Core
	{
		template <typename T>
		class PoolAllocator : public AbstractAllocator
		{
		private:
			struct ChunkNode {
				ChunkNode* nextFreeChunk;
			};

			std::size_t chunksPerBlock;
			ChunkNode* freeChunkNodeList;

		protected:
			void* Allocate(std::size_t size, std::uint8_t align) override;

			void Deallocate(void*& pointer) override;

		public:
			PoolAllocator() = delete;
			PoolAllocator(const PoolAllocator&) = delete;
			PoolAllocator& operator=(const PoolAllocator&) = delete;

			PoolAllocator(std::size_t objectsPerBlock);

			~PoolAllocator();

			T* New()
			{
				return new (Allocate(sizeof(T), alignof(T))) T;
			}

			template <typename... Args>
			T* NewWithArgs(Args&&... args)
			{
				return new (Allocate(sizeof(T), alignof(T))) T(std::forward<Args>(args)...);
			}

			template <typename... Args>
			void Delete(T* objectToDelete)
			{
				objectToDelete->~T();
				Deallocate(reinterpret_cast<void*&>(objectToDelete));
			}
		};
	}
}

#include "PoolAllocator.inl"
