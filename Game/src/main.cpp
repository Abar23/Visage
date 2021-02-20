#include <Math/Math.h>
#include "Rendering/RenderWindow.h"
#include "Core/MemoryManagement/StackAllocator.h"
#include "Core/MemoryManagement/PoolAllocator.h"
#include "Core/MemoryManagement/DoubleFrameAllocator.h"
#include "Core/MemoryManagement/FreeListAllocator.h"
#include "Math/Vec2.h"
#include "Rendering/RenderWindow.h"
#include <chrono>
#include <iostream>

int main()
{
	Visage::Core::FreeListAllocator list(1000 * 1000 * 1000);
	char* c = list.NewWithArgs<char>('c');
	int* p = list.NewWithArgs<int>(1);
	list.Delete(c);
	list.Delete(p);

	Visage::Core::PoolAllocator<Visage::vec2> allocator(3);

	// Record start time
	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 100000000; i++)
	{
		Visage::vec2* v1 = allocator.NewWithArgs(1, 2);
		Visage::vec2* v2 = allocator.NewWithArgs(1, 2);
		Visage::vec2* v3 = allocator.NewWithArgs(1, 2);

		allocator.Delete(v1);
		allocator.Delete(v2);
		allocator.Delete(v3);
	}
	
	// Record end time
	auto finish = std::chrono::high_resolution_clock::now();
	auto ellapsed = finish - start;
	std::cout << ellapsed.count() / 100000000.0f << std::endl;

	Visage::Core::StackAllocator allocator2(sizeof(Visage::vec2) * 3 + 16 * 3);

	// Record start time
	start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 100000000; i++)
	{
		Visage::vec2* v1 = allocator2.NewWithArgs<Visage::vec2>(1, 2);
		Visage::vec2* v2 = allocator2.NewWithArgs<Visage::vec2>(1, 2);
		Visage::vec2* v3 = allocator2.NewWithArgs<Visage::vec2>(1, 2);

		allocator2.Delete<Visage::vec2>(v3);
		allocator2.Delete<Visage::vec2>(v2);
		allocator2.Delete<Visage::vec2>(v1);
	}

	// Record end time
	finish = std::chrono::high_resolution_clock::now();
	ellapsed = finish - start;
	std::cout << ellapsed.count() / 100000000.0f << std::endl;

	// Record start time
	start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 100000; i++)
	{
		char* v1 = list.NewArray<char>(64000);

		list.DeleteArray(v1);
	}

	// Record end time
	finish = std::chrono::high_resolution_clock::now();
	ellapsed = finish - start;
	std::cout << ellapsed.count() / 100000.0f << std::endl;

	// Record start time
	start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 100000; i++)
	{
		char* v1 = new char[64000];

		delete v1;
	}

	// Record end time
	finish = std::chrono::high_resolution_clock::now();
	ellapsed = finish - start;
	std::cout << ellapsed.count() / 100000.0f << std::endl;

	return 0;
}