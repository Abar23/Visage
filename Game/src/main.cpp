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
	Visage::Core::FreeListAllocator list(80);
	char* c = list.NewWithArgs<char>('c');
	int* integer1 = list.NewWithArgs<int>(2);


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

	Visage::Core::StackAllocator allocator2(1024);
	Visage::ivec2* arr = allocator2.NewArray<Visage::ivec2>(2);
	arr[0] = { 1, 2 };
	arr[1] = { 2, 3 };
	std::cout << arr[1] << std::endl;
	std::cout << arr[0] << std::endl;
	allocator2.DeleteArray<Visage::ivec2>(arr);

	for (int i = 0; i < 1000000; i++)
	{
		char* c = allocator2.New<char>();
		Visage::vec2* v1 = allocator2.NewWithArgs<Visage::vec2>(1, 2);

		allocator2.Delete<Visage::vec2>(v1);
		allocator2.Delete<char>(c);
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

	Visage::Core::DoubleFrameAllocator doubleFrameAllocator(1024);
	int *j;
	for (size_t i = 0; i < 100; i++)
	{
		doubleFrameAllocator.SwapBuffers();
		doubleFrameAllocator.ClearCurrentBuffer();

		if (i > 0)
		{
			std::cout << "Last frame number: " << *j << std::endl;
			std::cout << "Memory used: " << doubleFrameAllocator.GetMemoryUsed() << std::endl;
			std::cout << "Number of allocations: " << doubleFrameAllocator.GetNumberOfAllocations() << std::endl;
		}

		j = doubleFrameAllocator.NewWithArgs<int>(i);
	}


	Visage::Rendering::RenderWindow window;
	window.Run();

	return 0;
}