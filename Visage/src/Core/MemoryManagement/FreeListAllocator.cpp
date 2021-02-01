#include "FreeListAllocator.h"
#include "MemoryUtils.h"

namespace Visage
{
	namespace Core
	{
		Visage::Core::FreeListAllocator::FreeListAllocator(std::size_t size)
			: AbstractAllocator(size)
		{
			assert(size >= sizeof(ListNode));

			freeListHead = reinterpret_cast<ListNode*>(startOfBuffer);
			freeListHead->size = size;
			freeListHead->nextListNode = nullptr;
		}

		FreeListAllocator::~FreeListAllocator()
		{
			freeListHead = nullptr;
		}

		void* FreeListAllocator::Allocate(std::size_t size, std::uint8_t align)
		{
			std::size_t neededSize = size + align + sizeof(AllocatonHeader);

			ListNode* freeNode = nullptr;
			ListNode* previousNode = nullptr;
			ListNode* currentNode = freeListHead;
			while (currentNode != nullptr)
			{
				if (neededSize <= currentNode->size)
				{
					freeNode = currentNode;
					break;
				}

				previousNode = currentNode;
				currentNode = currentNode->nextListNode;
			}

			if (freeNode == nullptr)
			{
				currentNode = IncreaseMemory(neededSize);
				freeNode = currentNode;
				freeListHead = currentNode;
			}

			std::uint8_t adjustmentForHeader = AlignedPointerWithHeaderAdjustment(freeNode, align, sizeof(AllocatonHeader));
			void* alignedAddress = AddToPointer(freeNode, adjustmentForHeader);
			void* headerAddress = SubtractFromPointer(alignedAddress, sizeof(AllocatonHeader));

			std::size_t totalAllocationSize = 0;
			if (freeNode->size >= neededSize + sizeof(ListNode))
			{
				totalAllocationSize = size + adjustmentForHeader;
				ListNode* newListNode = new (AddToPointer(alignedAddress, size)) ListNode(freeNode->size - totalAllocationSize, nullptr);
					
				if (previousNode == nullptr)
				{
					newListNode->nextListNode = currentNode->nextListNode;
					freeListHead = newListNode;
				}
				else
				{
					previousNode->nextListNode = newListNode;
					newListNode->nextListNode = currentNode->nextListNode;
				}
				currentNode->nextListNode = nullptr;
			}
			else
			{
				totalAllocationSize = freeNode->size;

				if (freeListHead == freeNode)
				{
					freeListHead = nullptr;
				}
			}

			AllocatonHeader* header = new (headerAddress) AllocatonHeader(totalAllocationSize, adjustmentForHeader);

			memoryUsed += totalAllocationSize;
			numberOfAllocations++;

			return alignedAddress;
		}

		void FreeListAllocator::Deallocate(void*& pointer)
		{
			AllocatonHeader* header = reinterpret_cast<AllocatonHeader*>(SubtractFromPointer(pointer, sizeof(AllocatonHeader)));
			ListNode* newNode = reinterpret_cast<ListNode*>(SubtractFromPointer(pointer, header->adjustment));

			memoryUsed -= newNode->size;
			numberOfAllocations--;

			AddNodeAndMergeRight(newNode);
		}

		FreeListAllocator::ListNode* FreeListAllocator::IncreaseMemory(std::uint8_t neededSpace)
		{
			void* newMemory = nullptr;
			if (neededSpace > size) // Replace with configurable memory increments later, if the incremented size is too small add the size of the object coming in
			{
				newMemory = new std::uint8_t[size + neededSpace];
			}
			else
			{
				newMemory = new std::uint8_t[size];
			}

			ListNode* newNode = new (newMemory) ListNode(size, nullptr);

			addedMemory.push_back(newMemory);

			return newNode;
		}

		void FreeListAllocator::AddNodeAndMergeRight(ListNode* newNode)
		{
			if (freeListHead == nullptr)
			{
				freeListHead = newNode;
				freeListHead->nextListNode = nullptr;
			}
			else
			{
				if (reinterpret_cast<std::uintptr_t>(newNode) < reinterpret_cast<std::uintptr_t>(freeListHead))
				{
					newNode->nextListNode = freeListHead;
					freeListHead = newNode;
					MergeWithRightNode(freeListHead);
				}
				else
				{
					ListNode* previousNode = nullptr;
					ListNode* currentNode = freeListHead;

					while (reinterpret_cast<std::uintptr_t>(currentNode) < reinterpret_cast<std::uintptr_t>(newNode) && currentNode != nullptr)
					{
						previousNode = currentNode;
						currentNode = currentNode->nextListNode;
					}

					newNode->nextListNode = previousNode->nextListNode;
					previousNode->nextListNode = newNode;
					MergeWithRightNode(newNode);
					MergeWithRightNode(previousNode);
				}
			}
		}

		void FreeListAllocator::MergeWithRightNode(ListNode* listNode)
		{
			if (listNode->nextListNode != nullptr)
			{
				std::uintptr_t startOfNextAddress = reinterpret_cast<std::uintptr_t>(AddToPointer(listNode, listNode->size));
				if (startOfNextAddress == reinterpret_cast<std::uintptr_t>(listNode->nextListNode))
				{
					listNode->size += listNode->nextListNode->size;
					listNode->nextListNode = listNode->nextListNode->nextListNode;
				}
			}
		}
	}
}
