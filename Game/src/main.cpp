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
	// Record start time
	auto start = std::chrono::high_resolution_clock::now();

	Visage::Core::PoolAllocator<Visage::vec2> allocator(1);

	for (int i = 0; i < 1000000; i++)
	{
		Visage::vec2* v1 = allocator.NewWithArgs(1, 2);

		allocator.Delete(v1);
	}
	
	// Record end time
	auto finish = std::chrono::high_resolution_clock::now();
	auto ellapsed = finish - start;
	std::cout << ellapsed.count() / 1000000.0f << std::endl;

	// Record start time
	start = std::chrono::high_resolution_clock::now();

	Visage::Core::StackAllocator allocator2(80);

	for (int i = 0; i < 1000000; i++)
	{
		Visage::vec2* v1 = allocator2.NewWithArgs<Visage::vec2>(1, 2);

		allocator2.Delete<Visage::vec2>(v1);
	}

	// Record end time
	finish = std::chrono::high_resolution_clock::now();
	ellapsed = finish - start;
	std::cout << ellapsed.count() / 1000000.0f << std::endl;

	// Record start time
	start = std::chrono::high_resolution_clock::now();

	Visage::Core::FreeListAllocator list(80);

	for (int i = 0; i < 1000000; i++)
	{
		Visage::vec2* v1 = list.NewWithArgs<Visage::vec2>(1, 2);

		list.Delete<Visage::vec2>(v1);
	}

	// Record end time
	finish = std::chrono::high_resolution_clock::now();
	ellapsed = finish - start;
	std::cout << ellapsed.count() / 1000000.0f << std::endl;

	// Record start time
	start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 1000000; i++)
	{
		Visage::vec2* v1 = new Visage::vec2(1, 2);

		delete v1;
	}

	// Record end time
	finish = std::chrono::high_resolution_clock::now();
	ellapsed = finish - start;
	std::cout << ellapsed.count() / 1000000.0f << std::endl;

	//Visage::Core::DoubleFrameAllocator doubleFrameAllocator(1024);
	//int *j;
	//for (size_t i = 0; i < 100; i++)
	//{
	//	doubleFrameAllocator.SwapBuffers();
	//	doubleFrameAllocator.ClearCurrentBuffer();

	//	if (i > 0)
	//	{
	//		std::cout << "Last frame number: " << *j << std::endl;
	//		std::cout << "Memory used: " << doubleFrameAllocator.GetMemoryUsed() << std::endl;
	//		std::cout << "Number of allocations: " << doubleFrameAllocator.GetNumberOfAllocations() << std::endl;
	//	}

	//	j = doubleFrameAllocator.NewWithArgs<int>(i);
	//}

	return 0;
}