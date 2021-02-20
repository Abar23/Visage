#pragma once

#include "AbstractAllocator.h"
#include <cstddef>
#include <vector>

namespace Visage
{
	namespace Core
	{
		class FreeListAllocator : public AbstractAllocator
		{
		private:
			struct ListNode {
				std::size_t size;
				ListNode* nextListNode;

				ListNode(std::size_t size, ListNode* nextListNode)
					: size(size), nextListNode(nextListNode)
				{ }
			};

			struct AllocatonHeader {
				std::size_t size;
				std::uint8_t adjustment;

				AllocatonHeader(std::size_t size, std::uint8_t adjustment)
					: size(size), adjustment(adjustment)
				{ }
			};
			
			ListNode* freeListHead;

			static const std::size_t allocationHeaderSize = sizeof(AllocatonHeader);

			static const std::size_t listNodeSize = sizeof(ListNode);

			void AddNodeAndMergeRight(ListNode* newNode);

			void MergeWithRightNode(ListNode* listNode);

		protected:
			void* Allocate(std::size_t size, std::uint8_t align) override;
			
			void Deallocate(void*& pointer) override;

		public:
			FreeListAllocator() = delete;

			FreeListAllocator(std::size_t size);

			~FreeListAllocator();

			void Defragment();

			template <typename T>
			T* New()
			{
				return new (Allocate(sizeof(T), alignof(T))) T;
			}

			template <typename T, typename... Args>
			T* NewWithArgs(Args&&... args)
			{
				return new (Allocate(sizeof(T), alignof(T))) T(std::forward<Args>(args)...);
			}

			template <typename T>
			T* NewArray(std::size_t arrayLength)
			{
				std::uint8_t numberOfElementsForOneWord = sizeof(size_t) / sizeof(T);

				if (sizeof(size_t) - (static_cast<std::size_t>(numberOfElementsForOneWord) * sizeof(T)) > 0)
				{
					numberOfElementsForOneWord += 1;
				}

				T* baseArrayAddress = reinterpret_cast<T*>(Allocate((arrayLength + numberOfElementsForOneWord) * sizeof(T), alignof(T))) + numberOfElementsForOneWord;
				*(reinterpret_cast<std::size_t*>(baseArrayAddress) - 1) = arrayLength;

				for (std::size_t i = 0; i < arrayLength; i++)
				{
					new (&baseArrayAddress[i]) T;
				}

				return baseArrayAddress;
			}

			template <typename T>
			void Delete(T* objectToDelete)
			{
				objectToDelete->~T();
				Deallocate(reinterpret_cast<void*&>(objectToDelete));
			}

			template <typename T>
			void DeleteArray(T* arrayToDelete)
			{
				std::size_t arrayLength = *(reinterpret_cast<std::size_t*>(arrayToDelete) - 1);

				for (std::size_t i = 0; i < arrayLength; i++)
				{
					arrayToDelete[i].~T();
				}

				arrayToDelete = reinterpret_cast<T*>(reinterpret_cast<std::size_t*>(arrayToDelete) - 1);
				Deallocate(reinterpret_cast<void*&>(arrayToDelete));
			}
		};
	}
}
