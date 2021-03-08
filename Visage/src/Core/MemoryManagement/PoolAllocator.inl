#pragma once

#include "PoolAllocator.h"
#include "MemoryUtils.h"

namespace Visage
{
	namespace Core
	{
		template <typename T>
		PoolAllocator<T>::PoolAllocator(std::size_t objectsPerBlock)
			: chunksPerBlock(objectsPerBlock)
		{ 
			assert(sizeof(T) >= sizeof(ChunkNode));

			sizeOfBuffer = (objectsPerBlock * sizeof(T)) + alignof(T);
			startOfBuffer = new std::uint8_t[sizeOfBuffer];
			
			std::uint8_t adjustment = AlignedPointerAdjustment(startOfBuffer, alignof(T));
			freeChunkNodeList = reinterpret_cast<ChunkNode*>(AddToPointer(startOfBuffer, adjustment));
			
			ChunkNode* currentChunkNode = freeChunkNodeList;
			for (int i = 1; i < objectsPerBlock; i++)
			{
				ChunkNode* nextChunk = reinterpret_cast<ChunkNode*>(AddToPointer(currentChunkNode, sizeof(T)));
				currentChunkNode->nextFreeChunk = nextChunk;
				currentChunkNode = nextChunk;
			}
			currentChunkNode->nextFreeChunk = nullptr;
		}

		template <typename T>
		void* PoolAllocator<T>::Allocate(std::size_t size, std::uint8_t align)
		{
			assert(size == sizeof(T) && align == alignof(T));

			void* alignedAddress = nullptr;
			
			if (freeChunkNodeList != nullptr)
			{
				alignedAddress = freeChunkNodeList;
				freeChunkNodeList = freeChunkNodeList->nextFreeChunk;
				memoryUsed += sizeof(T);
				numberOfAllocations++;
			}

			return alignedAddress;
		}
		
		template <typename T>
		void PoolAllocator<T>::Deallocate(void*& pointer)
		{
			ChunkNode* newChunkNode = reinterpret_cast<ChunkNode*>(pointer);
			newChunkNode->nextFreeChunk = freeChunkNodeList;
			freeChunkNodeList = newChunkNode;
			memoryUsed -= sizeof(T);
			numberOfAllocations--;
		}
	}
}