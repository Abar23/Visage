#pragma once

#include <GLFW/glfw3.h>
#include <functional>

namespace Visage
{
	namespace Rendering
	{
		class RenderWindow
		{
		private:
			GLFWwindow* window = nullptr;

		public:
			RenderWindow();
			~RenderWindow();
			
			void Run();
		};
	}
}

