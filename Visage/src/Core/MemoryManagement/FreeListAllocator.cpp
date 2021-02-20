#include "FreeListAllocator.h"
#include "MemoryUtils.h"
#include <cstring>

namespace Visage
{
	namespace Core
	{
		Visage::Core::FreeListAllocator::FreeListAllocator(std::size_t size)
			: AbstractAllocator(size) 
		{
			assert(size >= listNodeSize);

			freeListHead = reinterpret_cast<ListNode*>(startOfBuffer);
			freeListHead->size = size;
			freeListHead->nextListNode = nullptr;
		}

		FreeListAllocator::~FreeListAllocator()
		{
			freeListHead = nullptr;
		}

		void FreeListAllocator::Defragment()
		{
			if (freeListHead != nullptr && freeListHead->nextListNode != nullptr)
			{
				ListNode* nextFreeNode = freeListHead->nextListNode;
				AllocatonHeader* headerOfAllocatedElement = reinterpret_cast<AllocatonHeader*>(AddToPointer(freeListHead, freeListHead->size));
				std::size_t sizeOfAllocatedElement = headerOfAllocatedElement->size;
				std::uint8_t adjustmentForAllocatedElement = headerOfAllocatedElement->adjustment;
				AddToPointer(std::memcpy(freeListHead, headerOfAllocatedElement, sizeOfAllocatedElement), adjustmentForAllocatedElement);
				
				std::size_t sizeOfFreeListHead = freeListHead->size;
				freeListHead = reinterpret_cast<ListNode*>(AddToPointer(freeListHead, sizeOfAllocatedElement));
				freeListHead->size = sizeOfFreeListHead + nextFreeNode->size;
				freeListHead->nextListNode = nextFreeNode->nextListNode;
			}
		}

		void* FreeListAllocator::Allocate(std::size_t size, std::uint8_t align)
		{
			void* alignedAddress = nullptr;

			if (freeListHead != nullptr) // should replace with assert to catch out of memory issue if freelist will not be able to expand
			{
				std::size_t sizeOfNewElement = size + allocationHeaderSize; // replace align with adjustment

				std::uint8_t adjustmentForHeader = 0;
				ListNode* freeNode = nullptr;
				ListNode* previousNode = nullptr;
				ListNode* currentNode = freeListHead;
				while (currentNode != nullptr)
				{
					if (sizeOfNewElement <= currentNode->size)
					{
						adjustmentForHeader = AlignedPointerWithHeaderAdjustment(currentNode, align, allocationHeaderSize);
						std::size_t totalSizeNeededForNewElement = (adjustmentForHeader - allocationHeaderSize) + sizeOfNewElement;
						if (totalSizeNeededForNewElement <= currentNode->size)
						{
							freeNode = currentNode;
							break;
						}
					}

					previousNode = currentNode;
					currentNode = currentNode->nextListNode;
				}

				if (freeNode != nullptr) // Not enough memory to allocate object
				{
					alignedAddress = AddToPointer(freeNode, adjustmentForHeader);
					void* headerAddress = freeNode;
					std::size_t totalAllocationSize = 0;
					if (freeNode->size >= sizeOfNewElement + listNodeSize)
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
					}
					else
					{
						totalAllocationSize = freeNode->size;

						if (freeNode == freeListHead)
						{
							freeListHead = freeNode->nextListNode;
						}
						else
						{
							previousNode->nextListNode = freeNode->nextListNode;
						}
					}

					AllocatonHeader* header = new (headerAddress) AllocatonHeader(totalAllocationSize, adjustmentForHeader);

					*(reinterpret_cast<std::uint8_t*>(alignedAddress) - 1) = header->adjustment;

					memoryUsed += totalAllocationSize;
					numberOfAllocations++;
				}
			}

			return alignedAddress;
		}

		void FreeListAllocator::Deallocate(void*& pointer)
		{
			std::uint8_t adjustmentForHeader = *(reinterpret_cast<std::uint8_t*>(pointer) - 1);
			std::size_t sizeOfAllocatedElement = *reinterpret_cast<std::size_t*>(SubtractFromPointer(pointer, adjustmentForHeader));
			memoryUsed -= sizeOfAllocatedElement;
			numberOfAllocations--;

			ListNode* newNode = reinterpret_cast<ListNode*>(SubtractFromPointer(pointer, adjustmentForHeader));
			AddNodeAndMergeRight(newNode);
		}

		void FreeListAllocator::AddNodeAndMergeRight(ListNode* newNode)
		{
			if (freeListHead == nullptr)
			{
				freeListHead = newNode;
				freeListHead->nextListNode = nullptr;
			}
			else if (reinterpret_cast<std::uintptr_t>(newNode) < reinterpret_cast<std::uintptr_t>(freeListHead))
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

				previousNode->nextListNode = newNode;
				newNode->nextListNode = currentNode;
				MergeWithRightNode(newNode);
				MergeWithRightNode(previousNode);
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
